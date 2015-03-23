#include <json/json.h>
#include "Door.h"
#include "MXLogger.h"
#include "NetServer.h"
#include "SerialPortManager.h"


namespace mxnavi {



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
		serial_command.data[3] = 0x00;
		current_command = STOP_ACTION;
		serial_command.data[5] = STOP_ACTION;
	}
	
}

bool Door::do_reply(unsigned int command)
{

	switch (command)
	{
	case POSITION1:
		switch (current_command)
		{
		case ON_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = STOP_ACTION;
			current_command = STOP_ACTION;
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
		case OFF1_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = OFF1_ACTION;
			current_command = OFF1_ACTION;
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
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
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
		case OFF1_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = OFF2_ACTION;
			current_command = OFF2_ACTION;
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
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
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
		case OFF1_ACTION:
			break;
		case OFF2_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = STOP_ACTION;
			current_command = STOP_ACTION;
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
		default:
			break;
		}
		break;
	case FAULT:
		serial_command.data[3] = 0x00;
		serial_command.data[5] = RESET_ACTION;
		current_command = RESET_ACTION;
		return SerialPortManager::get_instance().send_command(part_name, &serial_command);
	case ACT_FALSE:
		make_net_command(command);
		NetServer::get_instance().write(get_net_command());
		break;
	case EXCEPTION_ACT:
		serial_command.data[3] = 0x00;
		serial_command.data[5] = ON_ACTION;
		current_command = ON_ACTION;
		return true;
	default:
		break;
	}
	return false;
	/*
	if (part_ptr->get_ack_kind() == ACTION_TO_CONTROLLER) {
		//receive the the command form the serail, dispose and send command to the serial
		if (part_ptr->do_reply_action(command_section)) {
			//SerialPortManager::get_instance().send_command(part_ptr->get_name(), part_ptr->get_command());
			part_ptr->do_command();
		}
	} else if (part_ptr->get_ack_kind() == EXCEPTION_ACTION) {
		// do the exception action
		if (part_ptr->do_reply_action(command_section)) {
			//SerialPortManager::get_instance().send_command(part_ptr->get_name(), part_ptr->get_command());
			part_ptr->do_command();
		}

		//do the special case for the exception.
		if (part_ptr->do_reply_action(6)) {
			//SerialPortManager::get_instance().send_command(part_ptr->get_name(), part_ptr->get_command());
			part_ptr->do_command();
		}
	} else {
		// net upload kind case
		part_ptr->make_net_command(command_section);
		NetServer::get_instance().write(part_ptr->get_net_command());
	}
	*/
}

void Door::make_net_command(unsigned int command)
{
	Json::FastWriter writer;
	Json::Value value;
	switch(command) {
	case ACT_FALSE:
		value["result"] = "fault";
		value["part"] = part_name;
		net_command = writer.write(value);
		break;
	case UPLOAD_IRIS:
		value["result"] = "iris-open";
		value["part"] = part_name;
		net_command = writer.write(value);
		break;
	default:
		break;
	}
}


}