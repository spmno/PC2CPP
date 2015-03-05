#include "BackDoor.h"

namespace mxnavi {

BackDoor::BackDoor(void)
{
	serial_command.data[4] = 0x33;
	part_name = "back-door";
}


BackDoor::~BackDoor(void)
{
}

}