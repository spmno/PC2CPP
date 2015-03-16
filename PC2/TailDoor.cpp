#include "TailDoor.h"

namespace mxnavi {

TailDoor::TailDoor(void)
{
	serial_command.data[4] = 0x34;
	part_name = "tail-door";
}


TailDoor::~TailDoor(void)
{
}

}