#include <memory>
#include "SerialCommandDisposer.h"
#include "PartFactory.h"
#include "NetServer.h"
#include "SerialPortManager.h"

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
	std::shared_ptr<Part> part_ptr(part_factory.createPart(part));
	unsigned int command_section = command[6];

	//dispose the error first
	if (command_section == 0x04) {
		part_ptr->make_net_command(command_section);
		NetServer::get_instance().write(part_ptr->get_net_command());
	}

	if (part_ptr->get_ack_kind() == ACTION_TO_CONTROLLER) {
		part_ptr->do_reply_action(command_section);
		SerialPortManager::get_instance().send_command(part_ptr->get_name(), part_ptr->get_command());
	} else {
		part_ptr->make_net_command(command_section);
		NetServer::get_instance().write(part_ptr->get_net_command());
	}

}

}