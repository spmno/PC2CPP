#include "stdafx.h"
#include <thread>
#include <sstream>
#include <boost/format.hpp>
#include "SerialPortManager.h"
#include "MXLogger.h"
#include "Part.h"
#include "PartFactory.h"
#include "ReadSerialTask.h"

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
	try {
		// add serial port to the container.
		for (const auto on_port : on_serial_port_container) {
			io_service iosev; 
			serial_ports[on_port.first] = std::make_shared<boost::asio::serial_port>(iosev, on_port.first);
			serial_ports[on_port.first]->set_option(  serial_port::baud_rate( on_port.second.baudrate ) );                 
			serial_ports[on_port.first]->set_option(  serial_port::flow_control( serial_port::flow_control::none ) ); 
			serial_ports[on_port.first]->set_option(  serial_port::parity( serial_port::parity::none ) );            
			serial_ports[on_port.first]->set_option( serial_port::stop_bits(  serial_port::stop_bits::one ) );        
			serial_ports[on_port.first]->set_option(  serial_port::character_size( 8 ) );    
			ReadSerialTask read_task;
			std::thread read_thread(read_task, on_port.first, serial_ports[on_port.first], task_func);
			read_thread.detach();
			//send init to every serial port
			/*
			PartFactory &part_factory = PartFactory::get_instance();
			std::shared_ptr<Part> part_ptr = part_factory.createPart(on_port.first);
			part_ptr->make_init_command();
			send_command(part_ptr->get_name(), part_ptr->get_command());
			*/
		}
	} catch (const boost::system::system_error& e) {
		LOG_DEBUG << e.what();
		MessageBox(NULL, L"´®¿ÚÅäÖÃ´íÎó", NULL, MB_OK|MB_TOPMOST);
		ExitProcess(-1);
	}

	LOG_DEBUG << "Serial Port Init Successful!";
	return true;
}

bool SerialPortManager::send_command(const string& part, const SerialCommand* command) 
{
	LOG_DEBUG << __FUNCTION__;
	std::string port_name = part_port_table[part];
	//find the initialized serial
	if (serial_ports.find(port_name) == serial_ports.end()) {
		LOG_DEBUG << "cann't find " << port_name;
		return false;
	}
	for(int i = 0; i < command->count; ++i) {
		serial_ports[port_name]->write_some(boost::asio::buffer(command->data, command->size));
		if (command->size == 1) {
			boost::format fmt("%02X");
			for (int i = 0; i < 1; ++i) {
				fmt % (int)command->data[i];
			}
			LOG_DEBUG << "send  " << fmt.str();
		} else {
			boost::format fmt("%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X");
			for (int i = 0; i < SERIAL_COMMAND_LENGTH; ++i) {
				fmt % (int)command->data[i];
			}
			LOG_DEBUG << "send  " << fmt.str();
		}

	}

	return true;
}

void SerialPortManager::task_func(unsigned char data[])
{
	for (auto callback : update_function_container) {
		callback(data);
	}
}


void SerialPortManager::addUpdateFunction(std::function<void (const unsigned char*)> function)
{
	update_function_container.push_back(function);
}

}