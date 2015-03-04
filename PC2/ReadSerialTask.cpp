#include <boost/format.hpp>
#include "ReadSerialTask.h"
#include "MXLogger.h"
#include "Part.h"

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
	while(true) {
		serial_ptr->read_some(boost::asio::buffer(data, sizeof(data)));
		function(data);

		boost::format fmt("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X");
		for (int i = 0; i < SERIAL_COMMAND_LENGTH; ++i) {
			fmt % (int)data[i];
		}
		LOG_DEBUG << "receive  " << fmt.str();
	}
}