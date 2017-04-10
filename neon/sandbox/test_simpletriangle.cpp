#include <iostream>
#include "test_simpletriangle.h"
#include "renderer\renderer.h"
#include <vector>

bool TestSimpleTriangle::Init()
{
	Renderer* renderer = Renderer::get();
	GLuint progamId = renderer->GenerateShaderProgram("resources/shaders/base.vert", "resources/shaders/base.frag");

	GLuint bufferId = 0;
	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);

	GLfloat z_value = 0.5f;
	std::vector<GLfloat> vertexArray =
	{
		+0.0f, +1.0f, z_value,
		+1.0f, +0.0f, +0.0,
		+1.0f, -1.0f, z_value,
		+0.0f, +0.0f, +1.0,
		-1.0f, -1.0f, z_value,
		+0.0f, +1.0f, +0.0
	};
	glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

	return true;
}

bool TestSimpleTriangle::Update()
{
	return true;
}

bool TestSimpleTriangle::Render()
{
	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	return true;
}
