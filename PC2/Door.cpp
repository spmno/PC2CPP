#include "Door.h"
#include "MXLogger.h"

namespace mxnavi {

Door::Door(void)
{
	serial_command.data[3] = 0x01;
	serial_command.data[4] = 0x32;
}


Door::~Door(void)
{

}

void Door::make_serial_command(const std::string& action) 
{
	LOG_DEBUG << __FUNCTION__;
	if (action == "on") {
		current_current = 0x03;
	} else if (action == "off1") {
		current_current = 0x00;
	} else if (action == "off2") {
		current_current = 0x01;
	}
	serial_command.data[3] = 0x01;
}

void Door::make_net_command(unsigned int command)
{

}

}