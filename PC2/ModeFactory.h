#pragma once
#include <memory>
#include <string>
#include "NearCarMode.h"

namespace mxnavi {

class ModeFactory
{
public:
	ModeFactory(void);
	~ModeFactory(void);
	static std::shared_ptr<Mode> create_mode(std::string &mode_name);
};

}