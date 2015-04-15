#pragma once
#include "Relay.h"

namespace mxnavi {

class AudioSystem :
	public Relay
{
public:
	AudioSystem(void);
	~AudioSystem(void);
	virtual bool make_init_command();
};

}