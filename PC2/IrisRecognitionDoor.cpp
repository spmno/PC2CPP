#include "IrisRecognitionDoor.h"
#include "SerialPortManager.h"
#include "ModeManager.h"
#include "NetServer.h"

namespace mxnavi {

IrisRecognitionDoor::IrisRecognitionDoor(void)
{
	serial_command.data[4] = 0x31;
	part_name = "iris-door";
}


IrisRecognitionDoor::~IrisRecognitionDoor(void)
{

}

bool IrisRecognitionDoor::do_reply(unsigned int command) 
{

	switch (command)
	{
	case POSITION1:
		switch (current_command)
		{
		case ON_ACTION: 
			{
			serial_command.data[3] = 0x00;
			serial_command.data[5] = STOP_ACTION;
			current_command = STOP_ACTION;
			SerialPortManager::get_instance().send_command(part_name, &serial_command);
			std::string mode_name = "iris";
			ModeManager::get_instance().do_mode(mode_name);
			break;
			}

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
		{
			//std::string mode_name = "iris";
			//ModeManager::get_instance().do_mode(mode_name);
			serial_command.data[3] = 0x00;
			serial_command.data[5] = ON_ACTION;
			current_command = ON_ACTION;
			SerialPortManager::get_instance().send_command(part_name, &serial_command);
			make_net_command(UPLOAD_IRIS);
			NetServer::get_instance().write(get_net_command());
			break;
		}

	case POSITION3:
		switch (current_command)
		{
		case ON_ACTION:
			serial_command.data[3] = 0x00;
			serial_command.data[5] = ON_ACTION;
			current_command = ON_ACTION;
			return SerialPortManager::get_instance().send_command(part_name, &serial_command);
		case OFF1_ACTION:
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
	default:
		break;
	}
	return false;
}

}