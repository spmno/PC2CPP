#pragma once
#include <string>
#include <vector>

namespace mxnavi {

struct SerialPort
{
	std::string port_name;
	int baudrate;
	std::vector<std::string> part_name_container;
};

}