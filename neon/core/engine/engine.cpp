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

void Engine::Loop()
{
	neonInterface = NeonInterface::get();
	renderer = Renderer::get();
	application = Application::RegisterApplication();
	if (!application)
		ASSERT("no application to run");
	application->Init();
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