#include "neon_interface.h"
#include "engine\engine.h"
#include <algorithm>
#include "../engine/common.h"
#include "glfw_interface.h"
#include "sdl2_interface.h"

NeonInterface::NeonInterface()
{
}


NeonInterface::~NeonInterface()
{
}

NeonInterface* NeonInterface::CreateNeonWindow()
{
	NeonInterface* instance = nullptr;
#ifdef ANDROID_BUILD
    {
		instance = new SDL2Interface();
	}
#else
    std::string windowOptStr = GetFromCommandOption("-window");
	if (windowOptStr == "glfw")
	{
		instance = new GLFWInterface();
	}
	else if (windowOptStr == "sdl2")
	{
		instance = new SDL2Interface();
	}
	else if (windowOptStr == "fbdev")
	{
		ASSERT("fbdev not supported!");
	}
	else
	{
		std::cout << "No window system defined using SLD2" << std::endl;
		instance = new SDL2Interface();
	}
#endif

	if (instance)
		instance->Init();


	return instance;
}
void NeonInterface::ExitApplication()
{
	Engine::get()->ExitApplication();
}

double NeonInterface::GetDeltaTime()
{
	ASSERT("GetDeltaTime Not implemented");
	return 0.0;
}

NeonInterface *NeonInterface::instance = nullptr;
NeonInterface *NeonInterface::get()
{
	if (!instance)
	{
		instance = NeonInterface::CreateNeonWindow();
	}

	return instance;
}
void NeonInterface::destroy()
{
	if (instance)
	{
		instance->DeInit();
		delete instance;
	}	
	instance = nullptr;
}