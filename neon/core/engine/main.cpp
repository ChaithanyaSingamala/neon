#include <iostream>
#include "engine.h"

#ifdef ANDROID_BUILD
#include <SDL.h>
#define MAIN_FUNCTION	SDL_main
#else
#define MAIN_FUNCTION	main
#endif


int MAIN_FUNCTION(int argc, char **argv)
{
	std::cout << "starting with neon engine... " << std::endl;

	Engine *engine = Engine::get();

	engine->RegisterCommandLineArguments(argc, argv);

	engine->Loop();

	Engine::destroy();

	return 0;
}