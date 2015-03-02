#include "stdafx.h"
#include "PartFactory.h"
#include "FrontMidLight.h"
#include "Chair.h"
#include "AdjustableLight.h"
#include "Door.h"

namespace mxnavi {

Part* PartFactory::createPart(const std::string& part_name) 
{	
	if (part_name == "front-mid-light") {
		return new FrontMidLight();
	} else if (part_name == "front-door") {
		return new Door();
	} else if (part_name == "chair") {
		return new Chair();
	} else if (part_name == "adjustable-light") {
		return new AdjustableLight();
	}
	return NULL;
}

Part* PartFactory::createPart(unsigned int part_number)
{
	switch (part_number)
	{
	case 0x11:
		return new FrontMidLight();
	default:
		break;
	}
	return NULL;
}

PartFactory::PartFactory(void)
{

}


PartFactory::~PartFactory(void)
{
}

}