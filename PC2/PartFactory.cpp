#include "stdafx.h"
#include "PartFactory.h"
#include "FrontMidLight.h"
#include "Chair.h"
#include "AdjustableLight.h"
#include "Door.h"

namespace mxnavi {

Part* PartFactory::createPart(const std::string& part_name) 
{	
	return part_containner[part_name];
}

Part* PartFactory::createPart(unsigned int part_number)
{
	std::string &part_name = part_relationship_table[part_number];
	return part_containner[part_name];
}

PartFactory::PartFactory(void)
{
	part_containner["front-mid-light"] = new FrontMidLight();
	part_containner["front-door"] = new Door();
	part_containner["chair"] = new Chair();
	part_containner["adjustable-light"] = new AdjustableLight();

	part_relationship_table[0x11] = "front-mid-light";

}


PartFactory::~PartFactory(void)
{
	for (auto part : part_containner) {
		delete part.second;
	}
}

}