#pragma once
#include <string>
#include <map>
#include <memory>
#include <boost/noncopyable.hpp>
#include "Part.h"

namespace mxnavi {

class PartFactory : public boost::noncopyable
{
public:
	~PartFactory(void);
	static PartFactory & get_instance() 
	{
		static PartFactory part_factory;
		return part_factory;
	}
	std::shared_ptr<Part> & createPart(const std::string& part_name);
	std::shared_ptr<Part> & createPart(unsigned int part_number);
	std::map<std::string, std::shared_ptr<Part> > & get_part_container() { return part_containner; }
private:
	PartFactory();
	std::map<std::string, std::shared_ptr<Part> > part_containner;
	std::map<int, std::string> part_relationship_table;
};


}