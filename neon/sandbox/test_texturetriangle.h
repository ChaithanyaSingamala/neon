#include <iostream>
#include "engine\application.h"

class TestTextureTriangle : public Application
{
public:
	bool Init();
	bool Update();
	bool Render();
	void Test1TextureTriangle();

	void HandleKeyInput(int key, int action) override;
	virtual void HandleMouseButtonInputs(int button, int action) override;
	virtual void HandleMouseScrollInputs(double xoffset, double yoffset) override;
	virtual void HandleMouseCursorInputs(double xpos, double ypos) override;


};
