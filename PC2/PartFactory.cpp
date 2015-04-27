#include "stdafx.h"
#include "PartFactory.h"
#include "FrontMidLight.h"
#include "DriverSeat.h"
#include "CoDriverSeat.h"
#include "AdjustableLight.h"
#include "FrontDoor.h"
#include "BackDoor.h"
#include "SideAtmosphereLight.h"
#include "ThresholdAtmosphereLight.h"
#include "FrontSideLight.h"
#include "FrontLogoLight.h"
#include "BackMidLight.h"
#include "BackLogoLight.h"
#include "BackSideLight.h"
#include "MediaPlayer.h"
#include "TailDoor.h"
#include "IrisRecognitionDoor.h"
#include "DriverSeatMotor.h"
#include "CoDriverSeatMotor.h"
#include "IP.h"
#include "Wheel.h"
#include "WheelHandle.h"
#include "FrontWindowSheeting.h"
#include "SkyLightSheeting.h"
#include "LeftWindowSheeting.h"
#include "RightWindowSheeting.h"
#include "BackWindowSheeting.h"
#include "AudioSystem.h"
#include "FragranceLight.h"
#include "IPAtmosphereLight.h"
#include "SidePanelLight.h"
#include "AudioSystem.h"
#include "DashboardPower.h"
#include "LeftSeatPower.h"
#include "RightSeatPower.h"
#include "BackMidLightPower.h"
#include "BackSideLightPower.h"
#include "BackLogoLightPower.h"
#include "FrontMidLightPower.h"
#include "FrontDaytimeLightPower.h"
#include "SidePanelLightPower.h"
#include "SOS.h"

namespace mxnavi {

std::shared_ptr<Part> & PartFactory::createPart(const std::string& part_name) 
{	
	return part_containner[part_name];
}

std::shared_ptr<Part> & PartFactory::createPart(unsigned int part_number)
{
	std::string &part_name = part_relationship_table[part_number];
	return part_containner[part_name];
}

PartFactory::PartFactory(void)
{
	part_containner["front-mid-light"] = std::make_shared<FrontMidLight>();
	part_containner["head-light"] = std::make_shared<FrontSideLight>();
	part_containner["daytime-running-light"] = std::make_shared<FrontLogoLight>();
	part_containner["back-mid-light"] = std::make_shared<BackMidLight>();
	part_containner["back-side-light"] = std::make_shared<BackSideLight>();
	part_containner["back-logo-light"] = std::make_shared<BackLogoLight>();
	part_containner["front-door"] = std::make_shared<FrontDoor>();
	part_containner["back-door"] = std::make_shared<BackDoor>();
	part_containner["iris-door"] = std::make_shared<IrisRecognitionDoor>();
	part_containner["tail-door"] = std::make_shared<TailDoor>();
	part_containner["driver-seat"] = std::make_shared<DriverSeat>();
	part_containner["co-driver-seat"] = std::make_shared<CoDriverSeat>();
	part_containner["side-panel-light"] = std::make_shared<SidePanelLight>();
	part_containner["side-atmosphere-light"] = std::make_shared<SideAtmosphereLight>();
	part_containner["threshold-atmosphere-light"] = std::make_shared<ThresholdAtmosphereLight>();
	part_containner["ip-atmosphere-light"] = std::make_shared<IPAtmosphereLight>();
	part_containner["fragrance-light"] = std::make_shared<FragranceLight>();
	part_containner["media-player"] = std::make_shared<MediaPlayer>();
	part_containner["driver-seat-motor"] = std::make_shared<DriverSeatMotor>();
	part_containner["co-driver-seat-motor"] = std::make_shared<CoDriverSeatMotor>();
	part_containner["ip"] = std::make_shared<IP>();
	part_containner["wheel"] = std::make_shared<Wheel>();
	part_containner["wheel-handle"] = std::make_shared<WheelHandle>();
	part_containner["front-window-sheeting"] = std::make_shared<FrontWindowSheeting>();
	part_containner["sky-light-sheeting"] = std::make_shared<SkyLightSheeting>();
	part_containner["left-window-sheeting"] = std::make_shared<LeftWindowSheeting>();
	part_containner["right-window-sheeting"] = std::make_shared<RightWindowSheeting>();
	part_containner["back-window-sheeting"] = std::make_shared<BackWindowSheeting>();

	part_containner["audio-system"] = std::make_shared<AudioSystem>();

	//sos
	part_containner["sos"] = std::make_shared<SOS>();

	//power manager
	part_containner["back-logo-light-power"] = std::make_shared<BackLogoLightPower>();
	part_containner["back-mid-light-power"] = std::make_shared<BackMidLightPower>();
	part_containner["back-side-light-power"] = std::make_shared<BackSideLightPower>();
	part_containner["dashboard-power"] = std::make_shared<DashboardPower>();
	part_containner["front-daytime-light-power"] = std::make_shared<FrontDaytimeLightPower>();
	part_containner["front-mid-light-power"] = std::make_shared<FrontMidLightPower>();
	part_containner["left-seat-power"] = std::make_shared<LeftSeatPower>();
	part_containner["right-seat-power"] = std::make_shared<RightSeatPower>();
	part_containner["side-panel-light-power"] = std::make_shared<SidePanelLightPower>();

	part_relationship_table[0x11] = "front-mid-light";
	part_relationship_table[0x32] = "front-door";
	part_relationship_table[0x33] = "back-door";
	part_relationship_table[0x19] = "side-atmosphere-light";
	part_relationship_table[0x1a] = "threshold-atmosphere-light";
	part_relationship_table[0x31] = "iris-door";
}


PartFactory::~PartFactory(void)
{

}

}