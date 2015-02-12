#include "stdafx.h"
#include "FrontMidLight.h"

namespace mxnavi {

FrontMidLight::FrontMidLight(void)
{
	serial_command.data[4] = 0x11;
}


FrontMidLight::~FrontMidLight(void)
{
}

}