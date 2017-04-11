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

	void InterfaceWindowSizeUpdated(unsigned short width, unsigned short height);

	void Loop();
	void ExitApplication() { isExit = true; }

	static Engine *get();
	static void destroy();

	void RegisterCommandLineArguments(int argc, char **argv);
	std::vector<std::string> GetCommandLineArguments();

	void HandleKeyInputs(int key, int action);
	void HandleMouseScrollInputs(double xoffset, double yoffset);
	void HandleMouseCursorInputs(double xpos, double ypos);
	void HandleMouseButtonInputs(int button, int action);
};

