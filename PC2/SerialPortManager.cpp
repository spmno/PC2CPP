#include "stdafx.h"
#include <thread>
#include "SerialPortManager.h"
#include "MXLogger.h"
#include "Part.h"

namespace mxnavi {

using namespace boost::asio;

std::vector<std::function<void (const unsigned char*)> > SerialPortManager::update_function_container; 

SerialPortManager::SerialPortManager(void)
{

}


SerialPortManager::~SerialPortManager(void)
{
}

bool SerialPortManager::init()
{
	for (const auto on_port : on_serial_port_container) {
		io_service iosev; 
		serial_ports[on_port.first] = std::make_shared<boost::asio::serial_port>(iosev, on_port.first);
		serial_ports[on_port.first]->set_option(  serial_port::baud_rate( on_port.second.baudrate ) );                 
		serial_ports[on_port.first]->set_option(  serial_port::flow_control( serial_port::flow_control::none ) ); 
		serial_ports[on_port.first]->set_option(  serial_port::parity( serial_port::parity::none ) );            
		serial_ports[on_port.first]->set_option( serial_port::stop_bits(  serial_port::stop_bits::one ) );        
		serial_ports[on_port.first]->set_option(  serial_port::character_size( 8 ) );           
		std::thread read_thread(read_task, on_port.first, this);
		read_thread.detach();
	}
	LOG_DEBUG << "Serial Port Init Successful!";
	return true;
}

bool SerialPortManager::send_command(const string& part, const SerialCommand* command) 
{
	LOG_DEBUG << __FUNCTION__;
	std::string port_name = part_port_table[part];
	if (serial_ports.find(port_name) == serial_ports.end()) {
		return false;
	}
	for(int i = 0; i < command->count; ++i) {
		serial_ports[port_name]->write_some(boost::asio::buffer(command->data, command->size));
	}

	return true;
}

void SerialPortManager::read_task(std::string& port_name, SerialPortManager* self)
{
	unsigned char data[8];
	while(true) {
		self->serial_ports[port_name]->read_some(boost::asio::buffer(data, sizeof(data)));
			
		LOG_DEBUG << data;
	}
}

void SerialPortManager::addUpdateFunction(std::function<void (const unsigned char*)> function)
{
	update_function_container.push_back(function);
}

}