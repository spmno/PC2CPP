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

void Light::make_serial_command(const std::string& action)
{
	LOG_DEBUG << __FUNCTION__;
	if (action == "on") {
		serial_command.data[5] = 0x01;
	} else if (action == "off") {
		serial_command.data[5] = 0x00;
	} else if (action == "red-on") {
		serial_command.data[5] = 0x11;
	} else if (action == "red-off") {
		serial_command.data[5] = 0x12;
	} else if (action == "green-on") {
		serial_command.data[5] = 0x21;
	} else if (action == "green-off") {
		serial_command.data[5] = 0x22;
	} else if (action == "blue-on") {
		serial_command.data[5] = 0x31;
	} else if (action == "blue-off") {
		serial_command.data[5] = 0x32;
	} else if (action == "mix-on") {
		serial_command.data[5] = 0x41;
	} else if (action == "mix-off") {
		serial_command.data[5] = 0x42;
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