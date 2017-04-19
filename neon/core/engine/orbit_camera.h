#pragma once

#include "camera_base.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class OrbitCamera
{
	glm::float32 fov = 43.0f;
	glm::float32 farPlane = 0.1f;
	glm::float32 nearPlane = 100.0f;
	glm::float32 aspect = 1.0f;

	glm::vec3 center = glm::vec3(0.0);

	glm::float32 orbitAngle = 90.0f;
	glm::float32 orbitDistance = 4.0f;
	glm::float32 orbitHeight = 1.0f;

	glm::mat4	viewMatrix;
	glm::mat4	projectionMatrix;

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

public:
	OrbitCamera();
	virtual ~OrbitCamera();

	virtual glm::mat4 GetPerspectiveMatrix();

	virtual glm::mat4 GetViewMatrix();
	virtual void SetOrbitAngle(glm::float32 _angle);
	virtual void SetOrbitDistance(glm::float32 _distance);
	virtual void SetOrbitHeight(glm::float32 _height);
	virtual void SetOrbitCenter(glm::vec3 _center);

	virtual void Orbit(glm::float32 _speed);

	virtual void SetProjection(glm::float32 _fov = 0.0f, glm::float32 _near = 0.0f, glm::float32 _far = 0.0f, glm::float32 _aspect = 0.0f);

};