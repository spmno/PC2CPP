#include "Mode.h"

namespace mxnavi {

Mode::Mode(void)
{

}


Mode::~Mode(void)
{
}

void Mode::add_part_action(std::shared_ptr<Part>& part_ptr, std::string &action_name)
{
	part_ptr_container.push_back(part_ptr);
	action_container.push_back(action_name);
}

}