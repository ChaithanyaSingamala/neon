#pragma once

class Application
{
public:
	Application() {}
	virtual ~Application() {}

	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual bool Render() = 0;

	//inputs
	virtual void HandleKeyInput(int key, int action) {}
	virtual void HandleMouseButtonInputs(int button, int action) {}
	virtual void HandleMouseScrollInputs(double xoffset, double yoffset) {}
	virtual void HandleMouseCursorInputs(double xpos, double ypos) {}

	static 	Application *RegisterApplication();
};
