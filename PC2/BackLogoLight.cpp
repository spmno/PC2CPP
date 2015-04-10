#include "BackLogoLight.h"

namespace mxnavi {

BackLogoLight::BackLogoLight(void)
{
	part_name = "back-logo-light";
	serial_command.data[4] = 0x15;
}


BackLogoLight::~BackLogoLight(void)
{
}

}