#include <iostream>
#include "engine.h"

int main(int argc, char **argv)
{
	std::cout << "hello world " << std::endl;

	Engine *engine = Engine::get();

	engine->RegisterCommandLineArguments(argc, argv);

	engine->Loop();

	return 0;
}