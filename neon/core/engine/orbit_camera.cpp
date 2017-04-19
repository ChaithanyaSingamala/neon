#include "orbit_camera.h"
#include "engine.h"
#include "interface\neon_interface.h"
#include "glm\gtx\vector_angle.hpp"

void OrbitCamera::UpdateViewMatrix()
{
	viewMatrix = glm::mat4(1);
	if (orbitAngle > 360.f)
		orbitAngle -= 360.f;
	glm::vec3 posOffset = glm::vec3(0.0f);
	posOffset.x = orbitDistance * cos(glm::radians(orbitAngle));
	posOffset.y = orbitHeight;
	posOffset.z = orbitDistance * sin(glm::radians(orbitAngle));
	//posOffset *= position;
	std::cout << posOffset.x << "," << posOffset.z << std::endl;

	viewMatrix = glm::lookAt(posOffset, center, glm::vec3(0.0f,1.0f,0.0f));
}

void OrbitCamera::UpdateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(fov), NeonInterface::get()->Width() / (float)NeonInterface::get()->Height(), 0.1f, 1000.0f);
}

OrbitCamera::OrbitCamera()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

OrbitCamera::~OrbitCamera()
{
}

glm::mat4 OrbitCamera::GetPerspectiveMatrix()
{
	return projectionMatrix;
}


glm::mat4 OrbitCamera::GetViewMatrix()
{
	return viewMatrix;
}

void OrbitCamera::SetOrbitAngle(glm::float32 _angle)
{
	orbitAngle = _angle;
}

void OrbitCamera::SetOrbitDistance(glm::float32 _distance)
{
	orbitDistance = _distance;
}

void OrbitCamera::SetOrbitHeight(glm::float32 _height)
{
	orbitHeight = _height;
}

void OrbitCamera::SetOrbitCenter(glm::vec3 _center)
{
	center = _center;
	UpdateViewMatrix();
}

void OrbitCamera::Orbit(glm::float32 _speed)
{
	orbitAngle += _speed;
	UpdateViewMatrix();
}

void OrbitCamera::SetProjection(glm::float32 _fov, glm::float32 _near, glm::float32 _far, glm::float32 _aspect)
{
	if (!_fov)
		fov = _fov;
	if (!_near)
		nearPlane = _near;
	if (!_far)
		farPlane = _far;
	if (_aspect)
		aspect = _aspect;

	UpdateProjectionMatrix();
}
