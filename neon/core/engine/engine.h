#pragma once

#include <vector>
#include <string>

class Engine;
class Application;
class NeonInterface;
class Renderer;

class Engine
{
	static Engine *engine;
	std::vector<std::string> commandLineArguments;
	bool isExit = false;
	Application *application = nullptr;
	NeonInterface *neonInterface = nullptr;
	Renderer *renderer;
public:
	Engine();
	virtual ~Engine();

	void Loop();
	void ExitApplication() { isExit = true; }

	static Engine *get();
	static void destroy();

	void RegisterCommandLineArguments(int argc, char **argv);
	std::vector<std::string> GetCommandLineArguments();
};

