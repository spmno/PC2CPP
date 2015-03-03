#pragma once
#include <string>
#include <map>
#include <memory>
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
	std::shared_ptr<Part> createPart(const std::string& part_name);
	std::shared_ptr<Part> createPart(unsigned int part_number);
private:
	PartFactory();
	std::map<std::string, std::shared_ptr<Part> > part_containner;
	std::map<int, std::string> part_relationship_table;
};


}