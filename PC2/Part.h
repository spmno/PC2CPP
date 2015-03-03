#pragma once
#include <array>
#include <string>

namespace mxnavi {

#define SERIAL_COMMAND_LENGTH 14

struct SerialCommand 
{
	unsigned char data[SERIAL_COMMAND_LENGTH];
	int count;
	int size;
};

typedef enum _ACK_KIND {
	UPLOAD_TO_NET,
	ACTION_TO_CONTROLLER,
} AckKind;

class Part
{
public:
	Part(void);
	virtual void make_serial_command(const std::string& part) = 0;
	virtual void make_net_command(unsigned int command) = 0;
	virtual void do_reply_action(unsigned int status) {}
	SerialCommand* get_command() { return &serial_command; }
	std::string& get_net_command() { return net_command; }
	AckKind get_ack_kind() { return ack_kind; }
	std::string& get_name() { return part_name; }
protected:
	virtual ~Part(void);
	SerialCommand serial_command;
	std::string net_command;
	std::string part_name;
	std::string part_command;
	AckKind ack_kind;
};


}