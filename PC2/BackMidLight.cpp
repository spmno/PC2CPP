#include "BackMidLight.h"

namespace mxnavi {

BackMidLight::BackMidLight(void)
{
	part_name = "back-mid-light";
	serial_command.data[4] = 0x13;
}


BackMidLight::~BackMidLight(void)
{
}

}