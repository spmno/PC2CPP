#include "stdafx.h"
#include "PartFactory.h"
#include "FrontMidLight.h"
#include "Chair.h"
#include "AdjustableLight.h"
#include "Door.h"

namespace mxnavi {

std::shared_ptr<Part> PartFactory::createPart(const std::string& part_name) 
{	
	return part_containner[part_name];
}

std::shared_ptr<Part> PartFactory::createPart(unsigned int part_number)
{
	std::string &part_name = part_relationship_table[part_number];
	return part_containner[part_name];
}

PartFactory::PartFactory(void)
{
	part_containner["front-mid-light"] = std::make_shared<FrontMidLight>();
	part_containner["front-door"] = std::make_shared<Door>();
	part_containner["chair"] = std::make_shared<Chair>();
	part_containner["adjustable-light"] = std::make_shared<AdjustableLight>();

	part_relationship_table[0x11] = "front-mid-light";
	part_relationship_table[0x32] = "front-door";
}


PartFactory::~PartFactory(void)
{
}

}