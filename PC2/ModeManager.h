#pragma once
#include <map>
#include <memory>
#include <boost/noncopyable.hpp>
#include "Mode.h"

namespace mxnavi {

class ModeManager : public boost::noncopyable
{
public:
	static ModeManager &get_instance()
	{
		static ModeManager mode_manager;
		return mode_manager;
	}
	~ModeManager(void);
	void add_mode(std::string &mode_name, std::shared_ptr<Mode> mode_ptr)
	{
		mode_container[mode_name] = mode_ptr;
	}
	void do_mode(std::string &mode_name);
private:
	ModeManager(void);
	std::map<std::string, std::shared_ptr<Mode> > mode_container;
};

}