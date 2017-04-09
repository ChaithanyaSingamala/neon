#include "engine\application.h"
//#include "test_application.h"
#include "test_simpletriangle.h"

Application* Application::RegisterApplication()
{
	return new TestSimpleTriangle();
}