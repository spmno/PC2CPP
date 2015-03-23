#pragma once
#include "Part.h"

namespace mxnavi {

class SeatMotor : public Part
{
public:
	SeatMotor(void);
	~SeatMotor(void);
	virtual void make_serial_command(const std::string& command);
	virtual bool make_init_command();
	virtual void make_net_command(unsigned int command); 
	virtual bool do_reply(unsigned int command);
protected:
	unsigned char current_command;
};

}