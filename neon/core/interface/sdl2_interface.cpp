#include "sdl2_interface.h"
#include "../engine/common.h"
#include "../engine/engine.h"
#include <SDL.h>
#include <string>

SDL_GLContext sdlGL = 0;

void SDL2Interface::CalculateUpdateDeltaTime()
{
	static double lastTime = SDL_GetTicks();
	double currentTime = SDL_GetTicks();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

}

double SDL2Interface::GetDeltaTime()
{
	return deltaTime;
}

SDL2Interface::SDL2Interface()
{

}


SDL2Interface::~SDL2Interface()
{
}

bool SDL2Interface::Init()
{
	std::string windowOptStr = "";

	windowOptStr = GetFromCommandOption("-title");
	if (windowOptStr != "")
		title = windowOptStr;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initalize SDL: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_DisplayMode mode;
	SDL_GetDisplayMode(0, 0, &mode);

#ifdef ANDROID_BUILD
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	width = mode.w;
	height = mode.h;
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
#else
    windowOptStr = GetFromCommandOption("-width");
    if (windowOptStr != "")
        width = std::stoi(windowOptStr);

    windowOptStr = GetFromCommandOption("-height");
    if (windowOptStr != "")
        height = std::stoi(windowOptStr);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	Uint32 flags = SDL_WINDOW_OPENGL;
#endif

	SDL_Log("created window Width = %d. Height = %d\n", width, height);

	window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	if (window == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create the sdlWindow: %s\n", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	sdlGL = SDL_GL_CreateContext(window);

	windowOptStr = GetFromCommandOption("-vsync");
	if (windowOptStr != "")
		SDL_GL_SetSwapInterval(1);
	else
		SDL_GL_SetSwapInterval(0);

	return false;
}

bool SDL2Interface::Update()
{

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			ExitApplication();
		}
		else if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION || event.type == SDL_FINGERMOTION)
		{
			// no implementation right now
		}
	}		

	SDL_GL_SwapWindow(window);

	CalculateUpdateDeltaTime();
#if ENABLE_FPS_PRINT
	static double lastTime = SDL_GetTicks();
	static int nbFrames = 0;
	double currentTime = SDL_GetTicks();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) 
	{ 	
		char str[100];
		sprintf_s(str, "%s fps:%d", title.c_str(), nbFrames);
		SDL_SetWindowTitle(window, str);
		nbFrames = 0;
		lastTime += 1.0;
	}
#endif
	return true;
}

bool SDL2Interface::DeInit()
{
	
	return true;
}