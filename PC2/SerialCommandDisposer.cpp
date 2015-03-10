#include <memory>
#include <mutex>
#include "SerialCommandDisposer.h"
#include "PartFactory.h"
#include "NetServer.h"
#include "SerialPortManager.h"
#include "MXLogger.h"

namespace mxnavi {

SerialCommandDisposer::SerialCommandDisposer(void)
{
}


SerialCommandDisposer::~SerialCommandDisposer(void)
{
}

void SerialCommandDisposer::dispose(const unsigned char* command)
{
	PartFactory &part_factory = PartFactory::get_instance();
	unsigned char part = command[4];
	std::shared_ptr<Part> &part_ptr = part_factory.createPart(part);

	if (!part_ptr) {
		//MessageBox(NULL, L"´íÎó´®¿ÚÊý¾Ý", NULL, MB_OK|MB_TOPMOST);
		return;
		ExitProcess(-1);
	}

	unsigned int command_section = command[7];

	std::mutex mu;
	std::lock_guard<std::mutex> lock(mu);
	//dispose the error first
	if (command_section == 0x05) {
		part_ptr->make_net_command(command_section);
		NetServer::get_instance().write(part_ptr->get_net_command());
		return ;
	}

	if (part_ptr->get_ack_kind() == ACTION_TO_CONTROLLER) {
		//receive the the command form the serail, dispose and send command to the serial
		if (part_ptr->do_reply_action(command_section)) {
			SerialPortManager::get_instance().send_command(part_ptr->get_name(), part_ptr->get_command());
		}
	} else if (part_ptr->get_ack_kind() == EXCEPTION_ACTION) {
		// do the exception action
		if (part_ptr->do_reply_action(command_section)) {
			SerialPortManager::get_instance().send_command(part_ptr->get_name(), part_ptr->get_command());
		}

		//do the special case for the exception.
		if (part_ptr->do_reply_action(6)) {
			SerialPortManager::get_instance().send_command(part_ptr->get_name(), part_ptr->get_command());
		}
	} else {
		// net upload kind case
		part_ptr->make_net_command(command_section);
		NetServer::get_instance().write(part_ptr->get_net_command());
	}
}

}