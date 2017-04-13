#include <iostream>
#include "engine\application.h"

class TestSimpleTriangle : public Application
{
	int testId = 0;

	void Test1SingleTriangleDrawArrayNoShader();
	void Test2SingleTriangleDrawArray();
	void Test3TwoTriangleDrawArray();
	void Test4TwoTriangleDrawElements();
	void Test4ChangeVertexDepth();
	void Test5Model();
	void Test6ModelDrawElement();

public:
	bool Init();
	bool Update();
	bool Render();
	bool DeInit() {}

	void HandleKeyInput(int key, int action) override;

};
