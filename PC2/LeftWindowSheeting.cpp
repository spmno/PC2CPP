#include "LeftWindowSheeting.h"

namespace mxnavi {

LeftWindowSheeting::LeftWindowSheeting(void)
{
	part_name = "left-window-sheeting";
	serial_command.data[4] = 0x73;
}


LeftWindowSheeting::~LeftWindowSheeting(void)
{
}

}