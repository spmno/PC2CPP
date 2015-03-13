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
	part_containner["front-side-light"] = std::make_shared<FrontSideLight>();
	part_containner["front-logo-light"] = std::make_shared<FrontLogoLight>();
	part_containner["back-mid-light"] = std::make_shared<BackMidLight>();
	part_containner["back-side-light"] = std::make_shared<BackSideLight>();
	part_containner["back-logo-light"] = std::make_shared<BackLogoLight>();
	part_containner["front-door"] = std::make_shared<FrontDoor>();
	part_containner["back-door"] = std::make_shared<BackDoor>();
	part_containner["iris-recognition-door"] = std::make_shared<IrisRecognitionDoor>();
	part_containner["tail-door"] = std::make_shared<TailDoor>();
	part_containner["driver-seat"] = std::make_shared<DriverSeat>();
	part_containner["co-driver-seat"] = std::make_shared<CoDriverSeat>();
	part_containner["adjustable-light"] = std::make_shared<AdjustableLight>();
	part_containner["side-atmosphere-light"] = std::make_shared<SideAtmosphereLight>();
	part_containner["threshold-atmosphere-light"] = std::make_shared<ThresholdAtmosphereLight>();
	part_containner["media-player"] = std::make_shared<MediaPlayer>();

	part_relationship_table[0x11] = "front-mid-light";
	part_relationship_table[0x32] = "front-door";
	part_relationship_table[0x33] = "back-door";
	part_relationship_table[0x19] = "side-atmosphere-light";
	part_relationship_table[0x1a] = "threshold-atmosphere-light";
}


PartFactory::~PartFactory(void)
{
}

}