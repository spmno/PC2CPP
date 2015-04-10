#include "IP.h"
#include "MXLogger.h"

namespace mxnavi {

IP::IP(void)
{
	serial_command.data[4] = 0x41;
	part_name = "ip";
}


IP::~IP(void)
{
}

bool IP::make_init_command()
{
	return true;
}

void IP::make_serial_command(const std::string& action)
{
	LOG_DEBUG << __FUNCTION__;
	if (action == "i1") {
		serial_command.data[5] = 0x00;
	} else if (action == "i2") {
		serial_command.data[5] = 0x01;
	} 
}

void IP::make_net_command(unsigned int command) 
{

}

}