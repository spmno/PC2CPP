#include "ThresholdAtmosphereLight.h"

namespace mxnavi {

ThresholdAtmosphereLight::ThresholdAtmosphereLight(void)
{
	part_name = "threshold-atmosphere-light";
	serial_command.data[4] = 0x19;
}


ThresholdAtmosphereLight::~ThresholdAtmosphereLight(void)
{

}

}