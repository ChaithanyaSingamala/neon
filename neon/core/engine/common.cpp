#include "common.h"
#include "defines.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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
#if INTERFACE_SDL
	SDL_RWops *file = SDL_RWFromFile(_filename.c_str(), "r");
	if (file == NULL) ASSERT("file not found");

	Sint64 res_size = SDL_RWsize(file);
	char* res = (char*)malloc(res_size + 1);

	Sint64 nb_read_total = 0, nb_read = 1;
	char* buf = res;
	while (nb_read_total < res_size && nb_read != 0) {
		nb_read = SDL_RWread(file, buf, 1, (res_size - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read;
	}
	SDL_RWclose(file);
	if (nb_read_total != res_size) {
		free(res);
		return NULL;
	}

	res[nb_read_total] = '\0';

	std::string output = res;
	free(res);

	return output;

#else
	std::ifstream file(_filename);
	if (!file.good())
		ASSERT("fail to open file");

    std::string output = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    //LOG("\n@@@@@@@@@@@@@@@   \n%s\n   #########################\n", output.c_str());

	return output;
#endif
	
}
