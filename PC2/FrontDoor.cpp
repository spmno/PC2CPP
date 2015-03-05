#include "FrontDoor.h"

namespace mxnavi {

FrontDoor::FrontDoor(void)
{
	serial_command.data[4] = 0x32;
	part_name = "front-door";
}


FrontDoor::~FrontDoor(void)
{
}

}