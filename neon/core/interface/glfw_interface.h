#pragma once
#include "neon_interface.h"
#include <string>

class GLFWInterface: public NeonInterface
{
	unsigned short width = 800;
	unsigned short height = 600;
	std::string title = "Neon Engine";
public:
	GLFWInterface();
	virtual ~GLFWInterface();

	virtual bool Init();
	virtual bool Update();
	virtual bool DeInit();

};

