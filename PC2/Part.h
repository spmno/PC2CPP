#pragma once
#include <array>
#include <string>

namespace mxnavi {

#define SERIAL_COMMAND_LENGTH 14

struct SerialCommand 
{
	unsigned char data[SERIAL_COMMAND_LENGTH];
	int count;
	int size;
};

class Part
{
public:
	Part(void);
	virtual ~Part(void);
	virtual void make_serial_command(const std::string& part) = 0;
	virtual void make_net_command(unsigned int command) = 0;
	SerialCommand* get_command() { return &serial_command; }
	std::string& get_net_command() { return net_command; }
protected:
	SerialCommand serial_command;
	std::string net_command;
	std::string part_name;
	std::string part_command;
};


}