#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>
#include <functional>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include "SerialPort.h"
#include "Part.h"

namespace mxnavi {

class SerialPortManager : boost::noncopyable
{
public:
	static SerialPortManager& get_instance()
	{
		static SerialPortManager serial_port_manager;
		return serial_port_manager;
	}
	bool init();
	static void read_task(std::string& port_name, SerialPortManager* self);
	static void task_func(unsigned char data[]);
	std::map<std::string, SerialPort>& get_port_container() { return serial_port_container; }
	std::map<std::string, SerialPort>& get_on_port_container() { return on_serial_port_container; }
	std::map<std::string, std::string>& get_part_port_table() { return part_port_table; }
	~SerialPortManager(void);
	bool send_command(const std::string& part, const SerialCommand* command);
	static void addUpdateFunction(std::function<void (const unsigned char*)> function);
private:
	SerialPortManager(void);
	//com name - serial 
	std::map<std::string, SerialPort> serial_port_container;
	std::map<std::string, SerialPort> on_serial_port_container;
	std::map<std::string, std::string> part_port_table;
	std::map<std::string, std::shared_ptr<boost::asio::serial_port> > serial_ports;
	static std::vector<std::function<void (const unsigned char*)> > update_function_container; 
};

}