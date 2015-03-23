#include "FrontLogoLight.h"

namespace mxnavi {

FrontLogoLight::FrontLogoLight(void)
{
	part_name = "daytime-running-light";
	serial_command.data[4] = 0x13;
}


FrontLogoLight::~FrontLogoLight(void)
{
}

}