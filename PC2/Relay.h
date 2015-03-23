#pragma once
#include "Part.h"

namespace mxnavi {

class Relay : public Part
{
public:
	Relay(void);
	~Relay(void);
	virtual void make_serial_command(const std::string& part);
	virtual void make_net_command(unsigned int command);
	virtual bool make_init_command();
};

}