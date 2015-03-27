#include <boost/format.hpp>
#include <json/json.h>
#include "ReadSerialTask.h"
#include "MXLogger.h"
#include "Part.h"
#include "NetServer.h"

namespace mxnavi {

ReadSerialTask::ReadSerialTask(void)
{
}


ReadSerialTask::~ReadSerialTask(void)
{
}

void ReadSerialTask::operator()(std::string &com_name, std::shared_ptr<boost::asio::serial_port> &serial_ptr, std::function<void(unsigned char[])> function)
{
	this->com_name = com_name;
	LOG_DEBUG << __FUNCTION__;

	unsigned char data[SERIAL_COMMAND_LENGTH];
	try {
		while(true) {
			serial_ptr->read_some(boost::asio::buffer(data, sizeof(data)));
			function(data);

			boost::format fmt("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X");
			for (int i = 0; i < SERIAL_COMMAND_LENGTH; ++i) {
				fmt % (int)data[i];
			}
			LOG_DEBUG << "receive  " << fmt.str();
		}
	} catch(const boost::system::system_error& e) {
		LOG_DEBUG << e.what();
		Json::FastWriter writer;
		Json::Value value;
		value["result"] = "fault";
		value["part"] = com_name;
		string net_command = writer.write(value);
		NetServer::get_instance().write(net_command);
	}
}

}