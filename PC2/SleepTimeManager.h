#pragma once

#include <boost/noncopyable.hpp>
#include <string>
#include <map>

namespace mxnavi {

class SleepTimeManager
{
public:
	static SleepTimeManager &get_instance()
	{
		static SleepTimeManager sleep_time_mamanger;
		return sleep_time_mamanger;
	}
	~SleepTimeManager(void);
	float get_sleep_time(const std::string& name);
private:	
	SleepTimeManager(void);
	std::map<std::string, float> sleep_time_container;
};

}