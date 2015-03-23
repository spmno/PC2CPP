#pragma once
#include "door.h"

namespace mxnavi {

class IrisRecognitionDoor :
	public Door
{
public:
	IrisRecognitionDoor(void);
	~IrisRecognitionDoor(void);
	virtual bool do_reply(unsigned int command);
};

}