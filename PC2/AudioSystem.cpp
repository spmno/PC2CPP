#include "AudioSystem.h"

namespace mxnavi {

AudioSystem::AudioSystem(void)
{
	part_name = "audio-system";
	serial_command.data[4] = 0x76;
}


AudioSystem::~AudioSystem(void)
{
}

}