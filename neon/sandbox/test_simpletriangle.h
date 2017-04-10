#include <iostream>
#include "engine\application.h"

class TestSimpleTriangle : public Application
{
	void Test1SingleTriangleDrawArrayNoShader();
	void Test2SingleTriangleDrawArray();
	void Test3TwoTriangleDrawArray();
	void Test4TwoTriangleDrawElements();
	void Test4ChangeVertexDepth();
	void Test5Model();

public:
	bool Init();
	bool Update();
	bool Render();
};
