#include "neon_interface.h"
#include "engine\engine.h"
#include <algorithm>
#include "../engine/common.h"
#include "glfw_interface.h"

NeonInterface::NeonInterface()
{
}


NeonInterface::~NeonInterface()
{
}

NeonInterface* NeonInterface::CreateNeonWindow()
{
	NeonInterface* instance = nullptr;
	std::string windowOptStr = GetFromCommandOption("-window");
	if (windowOptStr == "glfw")
	{
		instance = new GLFWInterface();
	}
	else if (windowOptStr == "sld")
	{
		ASSERT("SDL not supported!");
	}
	else if (windowOptStr == "fbdev")
	{
		ASSERT("fbdev not supported!");
	}
	else
	{
		std::cout << "No window system defined using GLFW" << std::endl;
		instance = new GLFWInterface();
	}

	if (instance)
		instance->Init();


	return instance;
}
void NeonInterface::ExitApplication()
{
	Engine::get()->ExitApplication();
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