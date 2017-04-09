#pragma once
#include "neon_interface.h"
#include <string>
#include "GLFW\glfw3.h"

class GLFWInterface: public NeonInterface
{
	unsigned short width = 800;
	unsigned short height = 600;
	std::string title = "Neon Engine";

	GLFWwindow* window = nullptr;

public:
	GLFWInterface();
	virtual ~GLFWInterface();

	virtual bool Init();
	virtual bool Update();
	virtual bool DeInit();

};

