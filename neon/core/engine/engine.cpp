#include "engine.h"
#include "application.h"
#include "common.h"
#include <iostream>
#include "interface\neon_interface.h"
#include "renderer\renderer.h"

Engine * Engine::engine = nullptr;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::InterfaceWindowSizeUpdated(unsigned short width, unsigned short height)
{
	renderer->SetViewport();
}

void Engine::Loop()
{
	neonInterface = NeonInterface::get();
	renderer = Renderer::get();
	application = Application::RegisterApplication();
	if (!application)
		ASSERT("no application to run");
	if(!application->Init())
		ASSERT("application Init not implemented");

	while (!isExit)
	{
		application->Update();
		application->Render();
		neonInterface->Update();
	}
	Renderer::destroy();
	delete engine->application;
	engine->application = nullptr;
	NeonInterface::destroy();

}

void Engine::RegisterCommandLineArguments(int argc, char ** argv)
{
	for (int i = 0; i < argc; i++)
	{
		commandLineArguments.push_back(argv[i]);
	}
}

std::vector<std::string> Engine::GetCommandLineArguments()
{
	return commandLineArguments;
}

void Engine::HandleKeyInputs(int key, int action)
{
	if (application)
		application->HandleKeyInput(key, action);
}

void Engine::HandleMouseScrollInputs(double xoffset, double yoffset)
{
	if (application)
		application->HandleMouseScrollInputs(xoffset, yoffset);
}

void Engine::HandleMouseCursorInputs(double xpos, double ypos)
{
	if (application)
		application->HandleMouseCursorInputs(xpos, ypos);
}

void Engine::HandleMouseButtonInputs(int button, int action)
{
	if (application)
		application->HandleMouseButtonInputs(button, action);
}

double Engine::GetDeltaTime()
{
	neonInterface->GetDeltaTime();
	return 0.0;
}

Engine *Engine::get()
{
	if (!engine)
	{
		engine = new Engine();
	}

	return engine;
}

void Engine::destroy()
{
	if (engine)
		delete engine;
	engine = nullptr;
}