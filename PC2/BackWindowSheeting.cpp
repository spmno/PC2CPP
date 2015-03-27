#include "BackWindowSheeting.h"

namespace mxnavi {

BackWindowSheeting::BackWindowSheeting(void)
{
	part_name = "back-window-sheeting";
	serial_command.data[5] = 0x50;
}


BackWindowSheeting::~BackWindowSheeting(void)
{
}

}