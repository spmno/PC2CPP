#include "LeftWindowSheeting.h"

namespace mxnavi {

LeftWindowSheeting::LeftWindowSheeting(void)
{
	part_name = "left-window-sheeting";
	serial_command.data[5] = 0x30;
}


LeftWindowSheeting::~LeftWindowSheeting(void)
{
}

}