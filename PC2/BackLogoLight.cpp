#include "BackLogoLight.h"

namespace mxnavi {

BackLogoLight::BackLogoLight(void)
{
	part_name = "back-logo-light";
	serial_command.data[4] = 0x16;
}


BackLogoLight::~BackLogoLight(void)
{
}

}