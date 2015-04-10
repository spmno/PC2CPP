#pragma once
#include "adjustablelight.h"

namespace mxnavi {

class IPAtmosphereLight :
	public AdjustableLight
{
public:
	IPAtmosphereLight(void);
	~IPAtmosphereLight(void);
};

}