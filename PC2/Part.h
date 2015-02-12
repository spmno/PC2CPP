#pragma once
#include <array>
#include <string>

namespace mxnavi {

struct SerialCommand 
{
	unsigned char data[8];
	int count;
	int size;
};

class Part
{
public:
	Part(void);
	~Part(void);
	virtual void make_serial_command(const std::string& part) = 0;
	SerialCommand* get_command() { return &serial_command; }
protected:
	SerialCommand serial_command;
};


}