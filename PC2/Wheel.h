#pragma once
#include "part.h"


namespace mxnavi {

class Wheel :
	public Part
{
public:
	Wheel(void);
	~Wheel(void);
	virtual void make_serial_command(const std::string& part);
	virtual void make_net_command(unsigned int command);
	virtual bool make_init_command();
};

}