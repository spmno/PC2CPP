#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <string>
#include <json/json.h>
#include "GlobalConfig.h"
#include "MXLogger.h"
#include "SerialPort.h"
#include "SerialPortManager.h"
#include "ModeManager.h"
#include "PartFactory.h"

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
			// all port in the config file, include the off status's port
			std::map<std::string, SerialPort>& serial_port_container = serial_port_manager.get_port_container();
			// just port which status is on.
			std::map<std::string, SerialPort>& on_serial_port_container = serial_port_manager.get_on_port_container();
			// the relationship of port and part.
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
				
				// mode configuration part
				ModeManager &mode_manager = ModeManager::get_instance();
				const Json::Value mode_array_value = value["mode"];
				for (auto mode_item : mode_array_value) {
					std::string mode_name = mode_item["name"].asString();
					LOG_DEBUG << "mode name: " << mode_name;
					//std::shared_ptr<Mode> mode_ptr = ModeFactory::create_mode(mode_name);
					Mode mode;
					
					const Json::Value action_array = mode_item["actions"];
					for (auto action : action_array) {
						Json::Value::Members members = action.getMemberNames();
						std::string part_name = *members.begin();
						std::shared_ptr<Part> &part_ptr = PartFactory::get_instance().createPart(part_name);
						if (!part_ptr) {
							MessageBox(NULL, L"²¿¼þ´íÎó", NULL, MB_OK|MB_TOPMOST);
							ExitProcess(-1);
						}
						mode.add_part_action(part_ptr, action[part_name].asString());
						LOG_DEBUG << "part: " << part_name << ", action: " << action[part_name].asString();
						if (members.size() > 1) {
							float sleep_time = action["sleep"].asFloat();
							mode.add_sleep(part_name, sleep_time);
						}
					}
					// add mode to mode manager
					mode_manager.add_mode(mode_name, mode);
				}
				
			} else {
				LOG_ERROR << "parse config file error!";
				return false;
			}
			// catch all exception here
		} catch(std::exception e) {
			LOG_ERROR << e.what();
			return false;
		}


	}
	return true;
}

}