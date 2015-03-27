#include "FrontWindowSheeting.h"

namespace mxnavi {

FrontWindowSheeting::FrontWindowSheeting(void)
{
	part_name = "front-window-sheeting";
	serial_command.data[5] = 0x10;
}


FrontWindowSheeting::~FrontWindowSheeting(void)
{
}

}