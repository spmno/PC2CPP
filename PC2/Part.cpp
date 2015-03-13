#include "stdafx.h"
#include "Part.h"
#include "SerialPortManager.h"

namespace mxnavi {

Part::Part(void) 
{
	serial_command.data[0] = 0xCF;
	serial_command.data[1] = 0xCF;
	serial_command.data[2] = 0;
	serial_command.data[3] = 0;
	serial_command.data[4] = 0;
	serial_command.data[5] = 0;
	serial_command.data[6] = 0;
	serial_command.data[7] = 0;
	serial_command.data[8] = 0;
	serial_command.data[9] = 0;
	serial_command.data[10] = 0;
	serial_command.data[11] = 0;
	serial_command.data[12] = 0xDD;
	serial_command.data[13] = 0xDD;
	serial_command.count = 1;
	serial_command.size = SERIAL_COMMAND_LENGTH;


}


Part::~Part(void)
{
}

bool Part::do_command() 
{
	return SerialPortManager::get_instance().send_command(part_name, &serial_command);
}

}