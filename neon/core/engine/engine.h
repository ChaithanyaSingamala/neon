#pragma once

#include <vector>
#include <string>

class Engine;
class Application;
class NeonInterface;

class Engine
{
	static Engine *engine;
	std::vector<std::string> commandLineArguments;
	bool isExit = false;
	Application *application = nullptr;
	NeonInterface *neonInterface = nullptr;
public:
	Engine();
	virtual ~Engine();

	void Loop();

	static Engine *get();

	void RegisterCommandLineArguments(int argc, char **argv);
	std::vector<std::string> GetCommandLineArguments();
};

