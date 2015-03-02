#pragma once
#include <string>
#include <map>
#include "Part.h"

namespace mxnavi {

class PartFactory
{
public:
	~PartFactory(void);
	static PartFactory & get_instance() 
	{
		static PartFactory part_factory;
		return part_factory;
	}
	Part* createPart(const std::string& part_name);
	Part* createPart(unsigned int part_number);
private:
	PartFactory();
	std::map<std::string, Part*> part_containner;
	std::map<int, std::string> part_relationship_table;
};


}