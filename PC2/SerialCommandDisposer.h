#pragma once

namespace mxnavi {

class SerialCommandDisposer
{
public:
	SerialCommandDisposer(void);
	~SerialCommandDisposer(void);
	void dispose(const unsigned char* command);
};

}