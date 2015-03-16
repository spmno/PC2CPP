#include "FrontSideLight.h"

namespace mxnavi {

FrontSideLight::FrontSideLight(void)
{
	part_name = "front-side-light";
	serial_command.data[4] = 0x12;
}


FrontSideLight::~FrontSideLight(void)
{
}

}