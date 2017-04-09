#include <iostream>
#include "test_application.h"

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
	return false;
}

Application* Application::RegisterApplication()
{
	return new TestApplication();
}