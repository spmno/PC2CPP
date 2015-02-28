#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <string>
#include <json/json.h>
#include "GlobalConfig.h"
#include "MXLogger.h"
#include "SerialPort.h"
#include "SerialPortManager.h"

namespace mxnavi {

GlobalConfig::GlobalConfig() : config_file_name("config.json")
{

}

bool GlobalConfig::init()
{
	std::ifstream config_stream(config_file_name);
	if (config_stream.good()) {
		try {
			Json::Reader reader;
			Json::Value value;
			SerialPortManager& serial_port_manager = SerialPortManager::get_instance();
			std::map<std::string, SerialPort>& serial_port_container = serial_port_manager.get_port_container();
			std::map<std::string, SerialPort>& on_serial_port_container = serial_port_manager.get_on_port_container();
			std::map<std::string, std::string>& part_port_table = serial_port_manager.get_part_port_table(); 
			if (reader.parse(config_stream, value)) {
				const Json::Value serial_array_value = value["serial"];
				for (auto port : serial_array_value) {
					SerialPort serialport;
					Json::Value::Members part_member = port.getMemberNames();
					// get part name as the map key
					std::string port_name = *(part_member.begin());
					int baudrate = port[port_name]["baudrate"].asInt();
					LOG_DEBUG << baudrate;
					Json::Value part_array_value = port[port_name]["parts"];
					serialport.port_name = port_name;
					serialport.baudrate = baudrate;
					for (auto part : part_array_value) {
						part_port_table[part.asString()] = port_name;
						serialport.part_name_container.push_back(part.asString());
					}
					serial_port_container[port_name] = serialport;
					if (port[port_name]["status"].asString() == "on") {
						on_serial_port_container[port_name] = serialport;
					}
				}
			} else {
				LOG_ERROR << "parse config file error!";
				return false;
			}
		} catch(std::exception e) {
			LOG_ERROR << e.what();
			return false;
		}


	}
	return true;
}

}