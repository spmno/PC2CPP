#pragma once
#include <string>
#include <boost/noncopyable.hpp>

namespace mxnavi {

class PartManager : boost::noncopyable
{
public:
	static PartManager& get_instance()
	{
		static PartManager part_manager;
		return part_manager;
	}
	~PartManager(void);
	void execute(const std::string& command);
private:
	PartManager(void);
};

}