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
	virtual bool do_reply_action(unsigned int status);
	virtual bool make_init_command();
private:
	unsigned char current_command;
};

}