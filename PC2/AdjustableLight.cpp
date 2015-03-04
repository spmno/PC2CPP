#include "AdjustableLight.h"
#include <vector>
#include <list>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


namespace mxnavi {

AdjustableLight::AdjustableLight(void)
{
	serial_command.data[4] = 0x19;
}


AdjustableLight::~AdjustableLight(void)
{
}

bool AdjustableLight::make_init_command()
{
	return true;
}

void AdjustableLight::make_serial_command(const std::string& command)
{
	std::vector<std::string> valueStringContainer;
	boost::split(valueStringContainer, command, boost::is_any_of(":"));
	int i = 4;
	for (auto value_str : valueStringContainer) {
		serial_command.data[++i] = boost::lexical_cast<int>(value_str);
	}
}

void AdjustableLight::make_net_command(unsigned int command)
{

}

}