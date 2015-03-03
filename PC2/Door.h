#pragma once
#include "Part.h"

namespace mxnavi {

class Door : public Part
{
public:
	Door(void);
	~Door(void);
	virtual void make_serial_command(const std::string& command);
	virtual void make_net_command(unsigned int command);
	virtual void do_reply_action(unsigned int status);
private:
	unsigned char current_command;
};

}