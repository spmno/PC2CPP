#include "ThresholdAtmosphereLight.h"

namespace mxnavi {

ThresholdAtmosphereLight::ThresholdAtmosphereLight(void)
{
	part_name = "threshold-atmosphere-light";
	serial_command.data[4] = 0x1A;
}


ThresholdAtmosphereLight::~ThresholdAtmosphereLight(void)
{
}

}