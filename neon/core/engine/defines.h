#pragma once

#include "engine.h"

#ifdef ANDROID_BUILD
#define	INTERFACE_SDL	1
#else
#define INTERFACE_SDL	1
#define INTERFACE_GLFW	0
#endif

#if INTERFACE_SDL
#include "SDL.h"
#define LOG	SDL_Log
#endif

#if INTERFACE_GLFW
#include <stdio.h>
#define LOG	printf
#endif


#include "renderer\opengl_header.h"

#define PATH_SEPRATER	"/"

#ifdef ANDROID_BUILD
#define RESOURCES_PATH	""
#else
#define RESOURCES_PATH	"resources/"
#endif

#define SHADER_PATH(x)	

