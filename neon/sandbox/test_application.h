#include <iostream>
#include "engine\application.h"

class Camera;

class TestApplication : public Application
{
public:
	virtual bool Init();
	virtual bool Update();
	virtual bool Render();
	virtual bool DeInit();

	virtual void HandleKeyInput(int key, int action) override;
	virtual void HandleMouseButtonInputs(int button, int action) override;
	virtual void HandleMouseScrollInputs(double xoffset, double yoffset) override;
	virtual void HandleMouseCursorInputs(double xpos, double ypos) override;

	Camera *camera;
};
