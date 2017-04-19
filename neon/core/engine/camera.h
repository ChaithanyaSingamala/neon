#pragma once

#include "camera_base.h"

class Camera: public CameraBase
{
	GLfloat lastX = 400, lastY = 300;
	bool firstMouse = true;
	bool freeCameraMouseLock = true;
	bool orbitCameraMouseLock = true;

public:
	virtual void HandleKeyInput(int key, int action);
	virtual void HandleMouseButtonInputs(int button, int action);
	virtual void HandleMouseScrollInputs(double xoffset, double yoffset);
	virtual void HandleMouseCursorInputs(double xpos, double ypos);

	virtual glm::mat4 GetPerspectiveMatrix();

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = -90.0f, GLfloat pitch = PITCH);
	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

};