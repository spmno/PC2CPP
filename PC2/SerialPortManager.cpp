#include "stdafx.h"
#include <thread>
#include <sstream>
#include <boost/format.hpp>
#include <json/json.h>
#include "SerialPortManager.h"
#include "NetServer.h"
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

std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen)

{
int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
if(nSize <= 0) return NULL;

WCHAR *pwszDst = new WCHAR[nSize+1];
if( NULL == pwszDst) return NULL;

MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
pwszDst[nSize] = 0;

if( pwszDst[0] == 0xFEFF) // skip Oxfeff
for(int i = 0; i < nSize; i ++)
pwszDst[i] = pwszDst[i+1];

std::wstring wcharString(pwszDst);
delete pwszDst;

return wcharString;
}

std::wstring s2ws(const string& s){ return Ansi2WChar(s.c_str(),s.size());} 

bool SerialPortManager::init()
{
	std::string current_port_name;
	try {
		// add serial port to the container.
		
		for (const auto on_port : on_serial_port_container) {
			io_service iosev; 
			current_port_name = on_port.first;
			serial_ports[on_port.first] = std::make_shared<boost::asio::serial_port>(iosev, on_port.first);
			serial_ports[on_port.first]->set_option(  serial_port::baud_rate( on_port.second.baudrate ) );                 
			serial_ports[on_port.first]->set_option(  serial_port::flow_control( serial_port::flow_control::none ) ); 
			serial_ports[on_port.first]->set_option(  serial_port::parity( serial_port::parity::none ) );            
			serial_ports[on_port.first]->set_option( serial_port::stop_bits(  serial_port::stop_bits::one ) );        
			serial_ports[on_port.first]->set_option(  serial_port::character_size( 8 ) );    
			ReadSerialTask read_task;
			std::thread read_thread(read_task, on_port.first, serial_ports[on_port.first], task_func);
			read_thread.detach();


			
		}
	} catch (const boost::system::system_error& e) {
		LOG_DEBUG << e.what();
		std::wstring w_com_name = s2ws(current_port_name);
		MessageBox(NULL, L"´®¿ÚÅäÖÃ´íÎó", w_com_name.c_str(), MB_OK|MB_TOPMOST);
		ExitProcess(-1);
	}

	for (auto part_pair : PartFactory::get_instance().get_part_container()) {
		if (part_pair.second->make_init_command()) {
			send_command(part_pair.second->get_name(), part_pair.second->get_command());
		}
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
		try {
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
		} catch(const boost::system::system_error& e) {
			LOG_DEBUG << e.what();
			Json::FastWriter writer;
			Json::Value value;
			value["result"] = "fault";
			value["part"] = port_name;
			string net_command = writer.write(value);
			NetServer::get_instance().write(net_command);
		}
	}

	return true;
}

void SerialPortManager::task_func(unsigned char data[])
{
	for (auto callback : update_function_container) {
		callback(data);
	}
//	std::for_each(update_function_container.begin(), update_function_container.end(), 
//		[=](std::function<void (const unsigned char*)> callback) { callback(data); });
}


void SerialPortManager::addUpdateFunction(std::function<void (const unsigned char*)> function)
{
	update_function_container.push_back(function);
}

}