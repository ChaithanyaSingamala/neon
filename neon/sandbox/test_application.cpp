#include <iostream>
#include "test_application.h"
#include "renderer\renderer.h"
#include "engine\camera.h"


bool TestApplication::Init()
{
	camera = new Camera();
	return true;
}

bool TestApplication::Update()
{
	return true;
}

bool TestApplication::Render()
{
	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return true;
}

bool TestApplication::DeInit()
{
	return false;
}

void TestApplication::HandleKeyInput(int key, int action)
{
	camera->HandleKeyInput(key, action);
	//std::cout << "key " << key << " " << action << " " << std::endl;
}

void TestApplication::HandleMouseButtonInputs(int button, int action)
{
	camera->HandleMouseButtonInputs(button, action);
	//std::cout << "mouse button " << button << " " << action << " " << std::endl;
}

void TestApplication::HandleMouseScrollInputs(double xoffset, double yoffset)
{
	camera->HandleMouseScrollInputs(xoffset, yoffset);
	//std::cout << "mouse scroll " << xoffset << " " << yoffset << " " << std::endl;
}

void TestApplication::HandleMouseCursorInputs(double xpos, double ypos)
{
	camera->HandleMouseCursorInputs(xpos, ypos);
	//std::cout << "mouse cursor " << xpos << " " << ypos << " " << std::endl;
}

