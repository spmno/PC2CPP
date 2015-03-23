#include "WheelHandle.h"
#include "MXLogger.h"

namespace mxnavi {

WheelHandle::WheelHandle(void)
{
	part_name = "wheel-handle";
	serial_command.data[4] = 0x52;
}


WheelHandle::~WheelHandle(void)
{
}

bool WheelHandle::make_init_command()
{
	return true;
}

void WheelHandle::make_serial_command(const std::string& action)
{
	LOG_DEBUG << __FUNCTION__;
	if (action == "b1") {
		serial_command.data[5] = 0x00;
	} else if (action == "b2") {
		serial_command.data[5] = 0x01;
	} 
}

void WheelHandle::make_net_command(unsigned int command) 
{

}

}