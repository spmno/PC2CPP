#include "Sheeting.h"

namespace mxnavi {

Sheeting::Sheeting(void)
{
	serial_command.data[4] = 0x72;
}


Sheeting::~Sheeting(void)
{
}

}