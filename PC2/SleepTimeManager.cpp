#include "SleepTimeManager.h"

namespace mxnavi {

SleepTimeManager::SleepTimeManager(void)
{
}


SleepTimeManager::~SleepTimeManager(void)
{
}

float SleepTimeManager::get_sleep_time(const std::string& name)
{
	return sleep_time_container[name];
}

}