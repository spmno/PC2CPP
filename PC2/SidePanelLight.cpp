#include "SidePanelLight.h"

namespace mxnavi {

SidePanelLight::SidePanelLight(void)
{
	part_name = "side-panel-light";
	serial_command.data[4] = 0x17;
}


SidePanelLight::~SidePanelLight(void)
{
}

}