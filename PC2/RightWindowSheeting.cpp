#include "RightWindowSheeting.h"

namespace mxnavi {

RightWindowSheeting::RightWindowSheeting(void)
{
	part_name = "right-window-sheeting";
	serial_command.data[4] = 0x74;
}


RightWindowSheeting::~RightWindowSheeting(void)
{
}

}