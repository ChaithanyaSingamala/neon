#include <iostream>
#include "test_application.h"
#include "glad\glad.h"

bool TestApplication::Init()
{
	return false;
}

bool TestApplication::Update()
{
	return false;
}

bool TestApplication::Render()
{
	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return false;
}

Application* Application::RegisterApplication()
{
	return new TestApplication();
}