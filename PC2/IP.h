#pragma once
#include "Part.h"

namespace mxnavi {

class IP 
	: public Part
{
public:
	IP(void);
	~IP(void);
	virtual void make_serial_command(const std::string& part);
	virtual void make_net_command(unsigned int command);
	virtual bool make_init_command();
};

}