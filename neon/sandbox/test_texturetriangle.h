#include <iostream>
#include "engine\application.h"

class Camera;

class TestTextureTriangle : public Application
{
	int testId = 0;
public:
	bool Init();
	bool Update();
	bool Render();
	bool DeInit() {}
	void Test1TextureTriangle();
	void Test2RotatingTextureCube();

	virtual void HandleKeyInput(int key, int action) override;
	virtual void HandleMouseButtonInputs(int button, int action) override;
	virtual void HandleMouseScrollInputs(double xoffset, double yoffset) override;
	virtual void HandleMouseCursorInputs(double xpos, double ypos) override;

	Camera *camera;
};
