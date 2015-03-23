#include "SeatMotor.h"
#include "MXLogger.h"
#include "SerialPortManager.h"

#define Z1		0
#define Z2		1
#define Z3		2

namespace mxnavi {

SeatMotor::SeatMotor(void)
{

}


SeatMotor::~SeatMotor(void)
{

}

bool SeatMotor::make_init_command()
{
	return false;
}

void SeatMotor::make_serial_command(const std::string& action) 
{
	LOG_DEBUG << __FUNCTION__;
	serial_command.data[3] = 0x00;
	if (action == "z1") {
		current_command = Z1;
		serial_command.data[5] = Z1;
	} else if (action == "z2") {
		current_command = Z2;
		serial_command.data[5] = Z2;
		//serial_command.data[5] = OFF1_ACTION;
	} else if (action == "z3") {
		current_command = Z3;
		serial_command.data[5] = Z3;
		//serial_command.data[5] = OFF2_ACTION;
	}
	
	//SerialPortManager::get_instance().send_command(part_name, &serial_command);
}

bool SeatMotor::do_reply(unsigned int command)
{

	switch (command)
	{
	case Z1:
		switch (current_command)
		{
		case Z1:
			break;
		case Z2:
		case Z3:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = Z1;
			current_command = Z1;
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
			break;
		default:
			break;
		}
		break;
	case Z2:
		switch (current_command)
		{
		case Z2:
			break;
		case Z1:
		case Z3:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = Z2;
			current_command = Z2;
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
		default:
			break;
		}
		break;
	case Z3:
		switch (current_command)
		{
		case Z3:
			break;
		case Z1:
		case Z2:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = Z3;
			current_command = Z3;
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
		default:
			break;
		}
		break;
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

void SeatMotor::make_net_command(unsigned int command)
{

}

}