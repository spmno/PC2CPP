#include <memory>
#include "SerialCommandDisposer.h"
#include "PartFactory.h"
#include "NetServer.h"

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
	if (part == 0x32) {

	} else {
		unsigned int command_section = command[6];
		std::unique_ptr<Part> part_ptr(part_factory.createPart(part));
		part_ptr->make_net_command(command_section);
		NetServer::get_instance().write(part_ptr->get_net_command());
	}

}

}