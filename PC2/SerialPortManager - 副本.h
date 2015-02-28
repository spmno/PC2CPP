#pragma once

#include <string>
#include <map>
#include <memory>
#include "SerialPort.h"

namespace mxnavi {

class SerialPortManager
{
public:
	static SerialPortManager& get_instance()
	{
		static SerialPortManager serial_port_manager;
		return serial_port_manager;
	}
	bool init();
	std::map<std::string, SerialPort>& get_port_container() { return serial_port_container; }
	std::map<std::string, SerialPort>& get_on_port_container() { return on_serial_port_container; }
	std::map<std::string, std::string>& get_part_port_table() { return part_port_table; }
	~SerialPortManager(void);
	void push_back_serial(std::string& name, SerialPort& port);
	void push_back_part_port_table(std::string& part_name, std::string& port_name);
private:
	SerialPortManager(void);
	//com name - serial 
	std::map<std::string, SerialPort> serial_port_container;
	std::map<std::string, SerialPort> on_serial_port_container;
	std::map<std::string, std::string> part_port_table;
	//std::map<std::string, std::unique_ptr<boost::asio::serial_port> > serial_ports;
};

}