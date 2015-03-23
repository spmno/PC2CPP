#pragma once
#include "Part.h"

namespace mxnavi {

//action
#define ON_ACTION		0x01
#define OFF1_ACTION		0x00
#define OFF2_ACTION		0x02
#define STOP_ACTION		0x03
#define RESET_ACTION	0x04

//status
#define POSITION1		0x01
#define POSITION2		0x02
#define POSITION3		0x03
#define FAULT			0x04
#define ACT_FALSE		0x05
#define EXCEPTION_ACT	0x06
#define UPLOAD_IRIS		0x07

class Door : public Part
{
public:
	Door(void);
	~Door(void);
	virtual void make_serial_command(const std::string& command);
	virtual void make_net_command(unsigned int command);
	virtual bool make_init_command();
	virtual bool do_reply(unsigned int command);
protected:
	unsigned char current_command;
};

}