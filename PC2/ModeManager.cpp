#include <Windows.h>
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
	if (mode_container.find(mode_name) != mode_container.end()) {
		Mode &mode = mode_container[mode_name];
		mode.do_mode(mode_name);
	} else {
		//MessageBox(NULL, L"无此模式", NULL, MB_OK|MB_TOPMOST);
	}

}

}