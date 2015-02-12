#include "stdafx.h"
#include "Chair.h"

namespace mxnavi {

Chair::Chair(void)
{
	serial_command.count = 10;
	serial_command.size = 1;
}


Chair::~Chair(void)
{
}

void Chair::make_serial_command(const std::string& action)
{
	if (action == "start") {
		serial_command.count = 15;
		serial_command.data[0] = 0x01;
	} else if (action == "stop") {
		serial_command.data[0] = 0x00;
	} else if (action == "header-up") {
		serial_command.data[0] = 0x45;
	} else if (action == "header-down") {
		serial_command.data[0] = 0x47;
	} else if (action == "back-up") {
		serial_command.data[0] = 0x96;
	} else if (action == "back-down") {
		serial_command.data[0] = 0x98;
	} else if (action == "hip-up") {
		serial_command.data[0] = 0xA5;
	} else if (action == "hip-down") {
		serial_command.data[0] = 0xA7;
	} else if (action == "foot-up") {
		serial_command.data[0] = 0xB6;
	} else if (action == "foot-down") {
		serial_command.data[0] = 0xB8;
	} else if (action == "waist-up") {
		serial_command.data[0] = 0xD5;
	} else if (action == "waist-down") {
		serial_command.data[0] = 0xD7;
	} else if (action == "straight") {
		serial_command.data[0] = 0x0E;
	} else if (action == "half-lay-down") {
		serial_command.data[0] = 0x0F;
	} else if (action == "lay-down") {
		serial_command.data[0] = 0x10;
	}
}

}