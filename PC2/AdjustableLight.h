#pragma once
#include "part.h"

namespace mxnavi {

class AdjustableLight :
	public Part
{
public:
	AdjustableLight(void);
	~AdjustableLight(void);
	virtual void make_serial_command(const std::string& command);
	virtual void make_net_command(unsigned int command);
};

}