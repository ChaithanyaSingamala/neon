#include <iostream>
#include "engine.h"

int main(int argc, char **argv)
{
	std::cout << "starting with neon engine... " << std::endl;

	Engine *engine = Engine::get();

	engine->RegisterCommandLineArguments(argc, argv);

	engine->Loop();

	Engine::destroy();

	return 0;
}