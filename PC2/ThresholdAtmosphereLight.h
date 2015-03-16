#pragma once
#include "adjustablelight.h"

namespace mxnavi {

class ThresholdAtmosphereLight :
	public AdjustableLight
{
public:
	ThresholdAtmosphereLight(void);
	~ThresholdAtmosphereLight(void);
};

}