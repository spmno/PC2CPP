#include <json/json.h>
#include "Door.h"
#include "MXLogger.h"


namespace mxnavi {

//action
#define ON_ACTION		0x02
#define OFF1_ACTION		0x00
#define OFF2_ACTION		0x01
#define STOP_ACTION		0x03
#define RESET_ACTION	0x04

//status
#define POSITION1		0x01
#define POSITION2		0x02
#define POSITION3		0x03
#define FAULT			0x04
#define ACT_FALSE		0x05

Door::Door(void)
{
	serial_command.data[3] = 0x01;
}


Door::~Door(void)
{

}

bool Door::make_init_command()
{
	return true;
}

void Door::make_serial_command(const std::string& action) 
{
	LOG_DEBUG << __FUNCTION__;
	serial_command.data[3] = 0x01;
	if (action == "open") {
		current_command = ON_ACTION;
		serial_command.data[5] = ON_ACTION;
	} else if (action == "off1") {
		current_command = OFF1_ACTION;
		//serial_command.data[5] = OFF1_ACTION;
	} else if (action == "off2") {
		current_command = OFF2_ACTION;
		//serial_command.data[5] = OFF2_ACTION;
	} else if (action == "close") {
		current_command = OFF1_ACTION;
		serial_command.data[5] = OFF1_ACTION;
	} else if (action == "stop") {
		current_command = STOP_ACTION;
		serial_command.data[5] = STOP_ACTION;
	}
	
	ack_kind = ACTION_TO_CONTROLLER;
}

void Door::make_net_command(unsigned int command)
{
	Json::FastWriter writer;
	Json::Value value;
	switch(command) {
	case 0x05:
		value["result"] = "fault";
		value["part"] = part_name;
		net_command = writer.write(value);
		break;
	}
}

bool Door::do_reply_action(unsigned int status) 
{
	switch (status)
	{
	case POSITION1:
		switch (current_command)
		{
		case ON_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = STOP_ACTION;
			current_command = STOP_ACTION;
			return true;
		case OFF1_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = OFF1_ACTION;
			current_command = OFF1_ACTION;
			return true;
		case OFF2_ACTION:
			break;
		default:
			break;
		}
		break;
	case POSITION2:
		switch (current_command)
		{
		case ON_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = ON_ACTION;
			current_command = ON_ACTION;
			return true;
		case OFF1_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = OFF2_ACTION;
			current_command = OFF2_ACTION;
			return true;
		case OFF2_ACTION:
			/*
			serial_command.data[3] = 0x00;
			serial_command.data[5] = STOP_ACTION;
			current_command = STOP_ACTION;
			return true;
			*/
			return false;
		default:
			break;
		}
		break;
	case POSITION3:
		switch (current_command)
		{
		case ON_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = ON_ACTION;
			current_command = ON_ACTION;
			return true;
		case OFF1_ACTION:
			break;
		case OFF2_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = STOP_ACTION;
			current_command = STOP_ACTION;
			return true;
		default:
			break;
		}
		break;
	case FAULT:
		serial_command.data[3] = 0x00;
		serial_command.data[5] = RESET_ACTION;
		current_command = RESET_ACTION;
		return true;
	default:
		break;
	}
	return false;
}

}