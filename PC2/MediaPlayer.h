#pragma once
#include "part.h"
#include <string>

namespace mxnavi {

class MediaPlayer :
	public Part
{
public:
	MediaPlayer(void);
	~MediaPlayer(void);
	virtual void make_serial_command(const std::string& action);
	virtual void make_net_command(unsigned int command);
	virtual bool make_init_command();
	virtual bool do_command();
private:
	std::string current_action;
	static void play_video();
	static bool play_flag;
};

}