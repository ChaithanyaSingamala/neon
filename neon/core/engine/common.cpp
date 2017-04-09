#include "common.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include "engine.h"

Common::Common()
{
}


Common::~Common()
{
}

void ASSERT(char *str)
{
	std::cout << "assert::" << str  << std::endl << "exiting..." <<std::endl;
	assert(0 && str);
	exit(0);
}

std::string GetFromCommandOption(std::string _for_value)
{
	std::string resultStr = "";
	Engine *engine = Engine::get();
	std::vector<std::string> list = engine->GetCommandLineArguments();
	auto result = std::find(list.begin(), list.end(), "-window");
	if (result != list.end())
	{
		if (result + 1 != list.end())
		{
			resultStr = *(result + 1);
		}
	}
	return resultStr;
}
