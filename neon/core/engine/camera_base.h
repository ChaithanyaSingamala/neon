#pragma once

/*
This code is direct copy of https://learnopengl.com Camera class
Thanks to https://learnopengl.com

*/

// Std. Includes
#include <vector>

// GL Includes
#include "defines.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 100.0f;
const GLfloat SENSITIVTY = 0.15f;
const GLfloat ZOOM = 43.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class CameraBase
{
public:
	// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		ORBIT_LEFT,
		ORBIT_RIGHT,
	};
	// CameraBase Attributes
	glm::vec3 Position;
	glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// CameraBase options
	GLfloat MovementSpeed = SPEED;
	GLfloat MouseSensitivity = SENSITIVTY;
	GLfloat Zoom = ZOOM;

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yoffset);

protected:
	// Calculates the front vector from the CameraBase's (updated) Eular Angles
	void updateCameraVectors();


};