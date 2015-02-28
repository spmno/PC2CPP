#pragma once
#include "Part.h"

namespace mxnavi {

class Light : public Part
{
public:
	Light(void);
	~Light(void);
	virtual void make_serial_command(const std::string& part);
	virtual void make_net_command(unsigned int command);
};

}

