#pragma once
#include <boost/noncopyable.hpp>



namespace mxnavi {

class GlobalConfig : boost::noncopyable
{
public:
	static GlobalConfig& get_instance()
	{
		static GlobalConfig global_config;
		return global_config;
	}
	
	bool init();
private:
	GlobalConfig();
	const std::string config_file_name;

};

}