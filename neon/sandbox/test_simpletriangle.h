#include <iostream>
#include "engine\application.h"

class TestSimpleTriangle : public Application
{
	void Test1SingleTriangleDrawArrayNoShader();
	void Test2SingleTriangleDrawArray();
	void Test3TwoTriangleDrawArray();
	void Test4TwoTriangleDrawElements();
public:
	bool Init();
	bool Update();
	bool Render();
};
