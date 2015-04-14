#include "Mode.h"
#include "MXLogger.h"
#include "SerialPortManager.h"

namespace mxnavi {

Mode::Mode(void)
{

}


Mode::~Mode(void)
{

}

void Mode::add_part_action(std::shared_ptr<Part>& part_ptr, std::string &action_name)
{
	//part_ptr_container.push_back(part_ptr);
	//action_container.push_back(action_name);
	action_container.push_back(std::make_pair(part_ptr, action_name));
}

void Mode::add_sleep(std::string& part_name, float sleep_time)
{
	sleep_conatainer[part_name] = sleep_time;
}

void Mode::do_mode(const std::string& name)
{
	for (auto action : action_container) {
		action.first->make_serial_command(action.second);
		//bool ret = SerialPortManager::get_instance().send_command(action.first->get_name(), action.first->get_command());
		bool ret = action.first->do_command();
		if (!ret) {
			LOG_ERROR << "write " << action.first->get_name() << " command failed!";
		}
		std::string sleep_name = name + "-" + action.first->get_name() + "-" + action.second;
		if (sleep_conatainer.find(sleep_name) != sleep_conatainer.end()) {
			float sleep_time = sleep_conatainer[sleep_name];
			LOG_ERROR << sleep_name << sleep_time;
			Sleep(sleep_time*1000);
		}
	}
}

}