#include "glfw_interface.h"
#include "../engine/common.h"
#include "../engine/engine.h"
#include "GLFW\glfw3.h"


void GLFWInterface::CalculateUpdateDeltaTime()
{
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

}

double GLFWInterface::GetDeltaTime()
{
	return deltaTime;
}

GLFWInterface::GLFWInterface()
{

}


GLFWInterface::~GLFWInterface()
{
}

void GLFWWindowSizeUpdated(GLFWwindow *window, int newwidth, int newheight)
{
	GLFWInterface::get()->Width(newwidth);
	GLFWInterface::get()->Height(newheight);

	Engine::get()->InterfaceWindowSizeUpdated(newwidth, newheight);
}

void GLFWkey_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_E && action == GLFW_PRESS);
	Engine::get()->HandleKeyInputs(key, action);
}
void GLFWcursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	Engine::get()->HandleMouseCursorInputs(xpos, ypos);
}

void GLFWmouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);
	Engine::get()->HandleMouseButtonInputs(button, action);
}

void GLFWscroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Engine::get()->HandleMouseScrollInputs(xoffset, yoffset);
}

bool GLFWInterface::Init()
{
	std::string windowOptStr = "";

	windowOptStr = GetFromCommandOption("-width");
	if (windowOptStr != "")
		width = std::stoi(windowOptStr);

	windowOptStr = GetFromCommandOption("-height");
	if (windowOptStr != "")
		height = std::stoi(windowOptStr);

	windowOptStr = GetFromCommandOption("-title");
	if (windowOptStr != "")
		title = windowOptStr;

	if (!glfwInit())
		ASSERT("GLFW failed to init!");

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		ASSERT("GLFW failed to to create window!");
	}

	glfwSetWindowSizeCallback(window, GLFWWindowSizeUpdated);

	glfwSetKeyCallback(window, GLFWkey_callback);
	glfwSetCursorPosCallback(window, GLFWcursor_pos_callback);
	glfwSetMouseButtonCallback(window, GLFWmouse_button_callback);
	glfwSetScrollCallback(window, GLFWscroll_callback);

	std::cout << "created window width=" << width << " height=" << height << std::endl;
	glfwMakeContextCurrent(window);

	windowOptStr = GetFromCommandOption("-vsync");
	if (windowOptStr != "")
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	return false;
}

bool GLFWInterface::Update()
{
	if (glfwWindowShouldClose(window))
		ExitApplication();

	glfwSwapBuffers(window);
	glfwPollEvents();

	CalculateUpdateDeltaTime();
#if ENABLE_FPS_PRINT
	static double lastTime = glfwGetTime();
	static int nbFrames = 0;
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) 
	{ 	
		char str[100];
		sprintf_s(str, "%s fps:%d", title.c_str(), nbFrames);
		glfwSetWindowTitle(window, str);
		nbFrames = 0;
		lastTime += 1.0;
	}
#endif
	return true;
}

bool GLFWInterface::DeInit()
{
	glfwTerminate();
	return true;
}
