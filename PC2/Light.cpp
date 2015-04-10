#include "stdafx.h"
#include <json/json.h>
#include "Light.h"
#include "MXLogger.h"

namespace mxnavi {

Light::Light(void)
{

}


Light::~Light(void)
{

}

bool Light::make_init_command()
{
	return true;
}

void Light::make_serial_command(const std::string& action)
{
	LOG_DEBUG << __FUNCTION__;
	if (action == "on") {
		serial_command.data[5] = 0x05;
	} else if (action == "twinkle-off") {
		serial_command.data[5] = 0x00;
	} else if (action == "twinkle") {
		serial_command.data[5] = 0x01;
	} else if (action == "on-gradually") {
		serial_command.data[5] = 0x03;
	} else if (action == "off-gradually") {
		serial_command.data[5] = 0x02;
	} else if (action == "off") {
		serial_command.data[5] = 0x04;
	} 
}

void Light::make_net_command(unsigned int command) 
{
	Json::FastWriter writer;
	Json::Value value;
	switch(command) {
	case 0x01:
		break;
	}
}

}