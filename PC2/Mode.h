#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Part.h"

namespace mxnavi {

class Mode
{
public:
	Mode(void);
	virtual ~Mode(void);
	void add_part_action(std::shared_ptr<Part>& part_ptr, std::string &action_name);
protected:
	std::vector<std::shared_ptr<Part> > part_ptr_container;
	std::vector<std::string> action_container;

	std::string mode_name;
};

}