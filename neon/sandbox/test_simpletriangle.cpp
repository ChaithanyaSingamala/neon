#include <iostream>
#include "test_simpletriangle.h"
#include "renderer\renderer.h"
#include <vector>

bool TestSimpleTriangle::Init()
{


	return true;
}

bool TestSimpleTriangle::Update()
{
	return true;
}

void TestSimpleTriangle::Test1SingleTriangleDrawArrayNoShader()
{
	static bool init = false;
	if (!init)
	{
		GLuint bufferId = 0;
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);

		GLfloat z_value = 0.5f;
		std::vector<GLfloat> vertexArray =
		{
			+0.0f, +1.0f, z_value,
			+1.0f, -1.0f, z_value,
			-1.0f, -1.0f, z_value,
		};
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void TestSimpleTriangle::Test2SingleTriangleDrawArray()
{
	static bool init = false;
	if (!init)
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
			+0.0f, +1.0f, +0.0,
		};
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void TestSimpleTriangle::Test3TwoTriangleDrawArray()
{
	static bool init = false;
	if (!init)
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
			+1.0f, +0.0f, z_value,
			+0.0f, +0.0f, +1.0,
			-1.0f, +0.0f, z_value,
			+0.0f, +1.0f, +0.0,

			+0.0f, -1.0f, z_value,
			+1.0f, +0.0f, +0.0,
			+1.0f, +0.0f, z_value,
			+0.0f, +0.0f, +1.0,
			-1.0f, +0.0f, z_value,
			+0.0f, +1.0f, +0.0

		};
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void TestSimpleTriangle::Test4TwoTriangleDrawElements()
{
	static bool init = false;
	if (!init)
	{
		Renderer* renderer = Renderer::get();
		GLuint progamId = renderer->GenerateShaderProgram("resources/shaders/base.vert", "resources/shaders/base.frag");

		GLfloat z_value = 0.5f;
		std::vector<GLfloat> vertexArray =
		{
			//0
			+0.0f, +1.0f, z_value,
			+1.0f, +0.0f, +0.0,
			//1
			+1.0f, +0.0f, z_value,
			+0.0f, +0.0f, +1.0,
			//2
			-1.0f, +0.0f, z_value,
			+0.0f, +1.0f, +0.0,
			//3
			+0.0f, -1.0f, z_value,
			+1.0f, +0.0f, +0.0,
		};
		std::vector<GLushort> indices = { 0,1,2, 3,1,2 };

		GLuint vertBufferId = 0;
		glGenBuffers(1, &vertBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, vertBufferId);
		glBufferData(GL_ARRAY_BUFFER, vertexArray.size() * sizeof(GLfloat), vertexArray.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0); //vertex position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1); //vertex color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

		GLuint indexBufferId = 0;
		glGenBuffers(1, &indexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

bool TestSimpleTriangle::Render()
{
	//Test1SingleTriangleDrawArrayNoShader();
	//Test2SingleTriangleDrawArray();
	//Test3TwoTriangleDrawArray();
	Test4TwoTriangleDrawElements();

	return true;
}
