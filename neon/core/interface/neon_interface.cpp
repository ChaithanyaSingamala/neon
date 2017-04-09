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

NeonInterface* NeonInterface::CreateWindow()
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

	}


	return instance;
}

NeonInterface *NeonInterface::instance = nullptr;
NeonInterface *NeonInterface::get()
{
	if (!instance)
	{
		instance = NeonInterface::CreateWindow();
	}

	return instance;
}