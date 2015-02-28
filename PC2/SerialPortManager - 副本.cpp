#include "stdafx.h"
#include "SerialPortManager.h"

namespace mxnavi {


SerialPortManager::SerialPortManager(void)
{
}


SerialPortManager::~SerialPortManager(void)
{
}

bool SerialPortManager::init()
{
	for (const auto on_port : on_serial_port_container) {
		//io_service iosev; 
		//std::unique_ptr<boost::asio::serial_port> serial_port_ptr(new serial_port(iosev, on_port.first));
		//serial_ports[on_port.first].reset(serial_port_ptr.release());
	}
	return true;
}

}