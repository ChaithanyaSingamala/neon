#include "engine\application.h"
//#include "test_application.h"
//#include "test_simpletriangle.h"
//#include "test_texturetriangle.h"
#include "test_lighting.h"

Application* Application::RegisterApplication()
{
	//return new TestSimpleTriangle();
	//return new TestTextureTriangle();
	return new TestLighting();
}