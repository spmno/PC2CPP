#include "FragranceLight.h"

namespace mxnavi {

FragranceLight::FragranceLight(void)
{
	part_name = "fragrance-light";
	serial_command.data[4] = 0x19;
}


FragranceLight::~FragranceLight(void)
{
}

}