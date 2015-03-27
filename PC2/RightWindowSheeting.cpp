#include "RightWindowSheeting.h"

namespace mxnavi {

RightWindowSheeting::RightWindowSheeting(void)
{
	part_name = "right-window-sheeting";
	serial_command.data[5] = 0x40;
}


RightWindowSheeting::~RightWindowSheeting(void)
{
}

}