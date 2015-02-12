#pragma once
#include "Part.h"

namespace mxnavi {

class Light : public Part
{
public:
	Light(void);
	~Light(void);
	virtual void make_serial_command(const std::string& part);
};

}

