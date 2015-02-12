#include "stdafx.h"
#include "Part.h"

namespace mxnavi {

Part::Part(void) 
{
	serial_command.data[0] = 0xCF;
	serial_command.data[1] = 0xCF;
	serial_command.data[2] = 0;
	serial_command.data[3] = 0;
	serial_command.data[4] = 0;
	serial_command.data[5] = 0;
	serial_command.data[6] = 0xDD;
	serial_command.data[7] = 0xDD;
	serial_command.count = 1;
	serial_command.size = 8;
}


Part::~Part(void)
{
}

}