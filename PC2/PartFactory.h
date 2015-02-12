#pragma once
#include <string>
#include "Part.h"

namespace mxnavi {

class PartFactory
{
public:
	PartFactory(void);
	~PartFactory(void);
	Part* createPart(const std::string& part_name);
	Part* createPart(unsigned int part_number);
};


}