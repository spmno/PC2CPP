#include "BackSideLight.h"

namespace mxnavi {

BackSideLight::BackSideLight(void)
{
	part_name = "back-side-light";
	serial_command.data[4] = 0x15;
}


BackSideLight::~BackSideLight(void)
{
}

}