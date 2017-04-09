#include <iostream>
#include "test_simpletriangle.h"
#include "renderer\renderer.h"
#include <vector>

bool TestSimpleTriangle::Init()
{
	GLfloat z_value = 0.0f;
	std::vector<GLfloat> vertexArray=
	{
		+0.0f, +1.0f, z_value,
		+1.0f, -1.0f, z_value,
		-1.0f, -1.0f, z_value
	};
	
	return false;
}

bool TestSimpleTriangle::Update()
{
	return false;
}

bool TestSimpleTriangle::Render()
{
	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return false;
}
