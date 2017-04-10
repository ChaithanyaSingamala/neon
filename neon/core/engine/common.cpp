#include "common.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "engine.h"

Common::Common()
{
}


Common::~Common()
{
}

#if 0
void ASSERT(char *str)
{
	std::cout << "assert::" << str  << std::endl << "exiting..." <<std::endl;
	assert(0 && str);
	exit(0);
}
#endif

std::string GetFromCommandOption(std::string _for_value)
{
	std::string resultStr = "";
	Engine *engine = Engine::get();
	std::vector<std::string> list = engine->GetCommandLineArguments();
	auto result = std::find(list.begin(), list.end(), _for_value);
	if (result != list.end())
	{
		if (result + 1 != list.end())
		{
			resultStr = *(result + 1);
		}
	}
	return resultStr;
}

std::string ReadFromFile(std::string _filename)
{
	std::ifstream file(_filename);
	if (!file.good())
		ASSERT("fail to open file");

	return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}
