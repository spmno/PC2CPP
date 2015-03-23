#include "BackWindowSheeting.h"

namespace mxnavi {

BackWindowSheeting::BackWindowSheeting(void)
{
	part_name = "back-window-sheeting";
	serial_command.data[4] = 0x75;
}


BackWindowSheeting::~BackWindowSheeting(void)
{
}

}