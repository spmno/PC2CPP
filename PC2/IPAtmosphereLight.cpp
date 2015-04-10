#include "IPAtmosphereLight.h"

namespace mxnavi {

IPAtmosphereLight::IPAtmosphereLight(void)
{
	part_name = "ip-atmosphere-light";
	serial_command.data[4] = 0x19;
}


IPAtmosphereLight::~IPAtmosphereLight(void)
{
}

}