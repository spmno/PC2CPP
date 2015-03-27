#include "SkyLightSheeting.h"

namespace mxnavi {

SkyLightSheeting::SkyLightSheeting(void)
{
	part_name = "sky-light-sheeting";
	serial_command.data[5] = 0x20;
}


SkyLightSheeting::~SkyLightSheeting(void)
{
}

}