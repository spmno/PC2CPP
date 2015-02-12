#include "stdafx.h"
#include <memory>
#include <json/json.h>
#include "PartFactory.h"
#include "MXLogger.h"
#include "PartManager.h"


namespace mxnavi {

PartManager::PartManager(void)
{
}


PartManager::~PartManager(void)
{
}

void PartManager::execute(const std::string& command)
{
	Json::Reader reader;
	Json::Value value;
	PartFactory part_factory;
	
	if (reader.parse(command, value)) {
		std::unique_ptr<Part> part_ptr(part_factory.createPart(value["part"].asString()));

	} else {
		LOG_ERROR << "Parse command failed!";
	}
}

}