#include "SideAtmosphereLight.h"

namespace mxnavi {

SideAtmosphereLight::SideAtmosphereLight(void)
{
	part_name = "side-atmosphere-light";
	serial_command.data[4] = 0x19;
}

SideAtmosphereLight::~SideAtmosphereLight(void)
{
}

}