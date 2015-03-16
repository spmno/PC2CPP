#pragma once
#include "Part.h"

namespace mxnavi {

class Seat : public Part
{
public:
	Seat(void);
	~Seat(void);
	virtual void make_serial_command(const std::string& action);
	virtual void make_net_command(unsigned int command);
	virtual bool make_init_command();
private:
	
};

}