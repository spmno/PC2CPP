#include "ModeFactory.h"
#include "NearCarMode.h"

namespace mxnavi {

ModeFactory::ModeFactory(void)
{
}

ModeFactory::~ModeFactory(void)
{
}

std::shared_ptr<Mode> ModeFactory::create_mode(std::string &mode_name)
{
	if (mode_name == "near-car") {
		return std::make_shared<NearCarMode>();
	}
	return nullptr;
}

}