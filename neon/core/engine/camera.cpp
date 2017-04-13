#include "camera.h"
#include "engine.h"
#include "interface\neon_interface.h"

void Camera::HandleKeyInput(int key, int action)
{
	if (action == 2)
	{
		switch (key)
		{
		case 87://w
			ProcessKeyboard(FORWARD, (GLfloat)Engine::get()->GetDeltaTime());
			break;
		case 83://s
			ProcessKeyboard(BACKWARD, (GLfloat)Engine::get()->GetDeltaTime());
			break;
		case 65://a
			ProcessKeyboard(LEFT, (GLfloat)Engine::get()->GetDeltaTime());
			break;
		case 68://d
			ProcessKeyboard(RIGHT, (GLfloat)Engine::get()->GetDeltaTime());
			break;
		case 341:	//left ctl
		case 345:	//right ctl
			mouseLock = false;
			break;

		}
	}
	else if (action == 0)
	{
		switch (key)
		{
		case 341:	//left ctl
		case 345:	//right ctl
			mouseLock = true;
			break;
		}
	}
	else if (action == 1)
	{
		switch (key)
		{
		case 341:	//left ctl
		case 345:	//right ctl
			mouseLock = false;
			break;
		}
	}
	//std::cout << "key " << key << " " << action << " " << std::endl;
}

void Camera::HandleMouseButtonInputs(int button, int action)
{
	//std::cout << "mouse button " << button << " " << action << " " << std::endl;
}

void Camera::HandleMouseScrollInputs(double xoffset, double yoffset)
{
	if(!mouseLock)
		ProcessMouseScroll((GLfloat)yoffset);
	//std::cout << "mouse scroll " << xoffset << " " << yoffset << " " << std::endl;
}

void Camera::HandleMouseCursorInputs(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (GLfloat)xpos;
		lastY = (GLfloat)ypos;
		firstMouse = false;
	}

	GLfloat xoffset = (GLfloat)(xpos - lastX);
	GLfloat yoffset = (GLfloat)(lastY - ypos);  // Reversed since y-coordinates go from bottom to left

	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;

	if (!mouseLock)
	{
		ProcessMouseMovement((GLfloat)xoffset, (GLfloat)yoffset);
	}
	//std::cout << "mouse cursor " << xpos << " " << ypos << " " << std::endl;
}

glm::mat4 Camera::GetPerspectiveMatrix()
{
	return glm::perspective(glm::radians(Zoom), NeonInterface::get()->Width() / (float)NeonInterface::get()->Height(), 0.1f, 1000.0f);
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
	this->Position = position; 
	this->WorldUp = up;
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
{
	this->Position = glm::vec3(posX, posY, posZ);
	this->WorldUp = glm::vec3(upX, upY, upZ);
	this->Yaw = yaw;
	this->Pitch = pitch;
	this->updateCameraVectors();
}

