#include "AudioSystem.h"

namespace mxnavi {

AudioSystem::AudioSystem(void)
{
	part_name = "audio-system";
	serial_command.data[4] = 0x73;
	serial_command.data[5] = 0x10;
}


AudioSystem::~AudioSystem(void)
{
}

}