#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Part.h"

namespace mxnavi {

class Mode
{
public:
	Mode(void);
	virtual ~Mode(void);
	void add_part_action(std::shared_ptr<Part>& part_ptr, std::string &action_name); 
	void add_sleep(std::string& part_name, int sleep_time);
	void do_mode();
protected:
	//std::vector<std::shared_ptr<Part> > part_ptr_container;
	//std::vector<std::string> action_container;
	std::vector<std::pair<std::shared_ptr<Part>, std::string> > action_container;
	std::map<std::string, int> sleep_conatainer;
	std::string mode_name;
};

}