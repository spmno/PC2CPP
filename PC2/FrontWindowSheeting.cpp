#include "FrontWindowSheeting.h"

namespace mxnavi {

FrontWindowSheeting::FrontWindowSheeting(void)
{
	part_name = "front-window-sheeting";
	serial_command.data[4] = 0x71;
}


FrontWindowSheeting::~FrontWindowSheeting(void)
{
}

}