#pragma once
#include <memory>
#include <boost/asio.hpp>

namespace mxnavi {

class ReadSerialTask
{
public:
	ReadSerialTask(void);
	~ReadSerialTask(void);
	void operator()(std::string& com_name, std::shared_ptr<boost::asio::serial_port> &serial_ptr, std::function<void(unsigned char[])>);
private:
	std::string com_name;
};

}