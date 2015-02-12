#pragma once
#include "Part.h"

namespace mxnavi {

class Chair : public Part
{
public:
	Chair(void);
	~Chair(void);
	virtual void make_serial_command(const std::string& part);
private:
	
};

}