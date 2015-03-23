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

	std::mutex mu;
	std::lock_guard<std::mutex> lock(mu);

	unsigned int command_section = command[7];
	part_ptr->do_reply(command_section);
}

}