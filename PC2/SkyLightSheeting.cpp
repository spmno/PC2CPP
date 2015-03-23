#include "SkyLightSheeting.h"

namespace mxnavi {

SkyLightSheeting::SkyLightSheeting(void)
{
	part_name = "sky-light-sheeting";
	serial_command.data[4] = 0x72;
}


SkyLightSheeting::~SkyLightSheeting(void)
{
}

}