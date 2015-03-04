#include "ModeManager.h"

namespace mxnavi {

ModeManager::ModeManager(void)
{
}


ModeManager::~ModeManager(void)
{
}

void ModeManager::do_mode(std::string &mode_name) 
{
	std::shared_ptr<Mode> &mode = mode_container[mode_name];
}

}