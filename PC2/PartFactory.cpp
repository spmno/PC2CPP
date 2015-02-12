#include "stdafx.h"
#include "PartFactory.h"
#include "FrontMidLight.h"
#include "Chair.h"

namespace mxnavi {

Part* PartFactory::createPart(const std::string& part_name) 
{	
	if (part_name == "front-mid-light") {
		return new FrontMidLight();
	} else if (part_name == "front-door") {

	} else if (part_name == "chair") {
		return new Chair();
	}
	return NULL;
}

Part* PartFactory::createPart(unsigned int part_number)
{
	switch (part_number)
	{

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