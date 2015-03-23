#include "Wheel.h"
#include "MXLogger.h"

namespace mxnavi {

Wheel::Wheel(void)
{
	part_name = "wheel";
	serial_command.data[4] = 0x51;
}


Wheel::~Wheel(void)
{

}

bool Wheel::make_init_command()
{
	return true;
}

void Wheel::make_serial_command(const std::string& action)
{
	LOG_DEBUG << __FUNCTION__;
	if (action == "f1") {
		serial_command.data[5] = 0x00;
	} else if (action == "f2") {
		serial_command.data[5] = 0x01;
	} 
}

void Wheel::make_net_command(unsigned int command) 
{

}

}