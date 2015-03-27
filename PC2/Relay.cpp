#include "Relay.h"
#include "MXLogger.h"

namespace mxnavi {

Relay::Relay(void)
{
	
}


Relay::~Relay(void)
{
}

bool Relay::make_init_command()
{
	return true;
}

void Relay::make_serial_command(const std::string& action)
{
	LOG_DEBUG << __FUNCTION__;
	if (action == "on") {
		serial_command.data[5] |= 0x01;
	} else if (action == "off") {
		serial_command.data[5] &= 0xF0;
	}
}

void Relay::make_net_command(unsigned int command) 
{

}

}