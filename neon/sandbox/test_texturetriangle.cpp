#include <iostream>
#include "test_texturetriangle.h"
#include "renderer\renderer.h"
#include "renderer\model.h"
#include "renderer\shader.h"
#include "SOIL.h"

bool TestTextureTriangle::Init()
{
	return true;
}

bool TestTextureTriangle::Update()
{
	return true;
}

bool TestTextureTriangle::Render()
{
	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Test1TextureTriangle();

	return true;
}

void LoadTexture(std::string _filename)
{
	int width, height;
	unsigned char* image;
	image = SOIL_load_image(_filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TestTextureTriangle::Test1TextureTriangle()
{
	static bool init = false;
	Shader *shader = new Shader("resources/shaders/v140/simpletexture.vert", "resources/shaders/v140/simpletexture.frag");
	shader->Bind();
	shader->BindAttributeLocation("vertexPosition", 0);
	shader->BindAttributeLocation("vertexColor", 1);

	LoadTexture("resources/textures/texture_4.png");

	static Model *model = 0;
	if (!init)
	{
		std::vector<GLfloat> vertexArray =
		{
			//  Position				Color					Texcoords
			-0.5f, +0.5f, +0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
			+0.5f, +0.5f, +0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
			+0.5f, -0.5f, +0.0f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
			-0.5f, -0.5f, +0.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
		};
		std::vector<GLushort> indices = { 0, 1, 2,  2, 3, 0 };
		ModelDataLayout layout;
		layout.position =	{ GL_TRUE, 0, 0, 8, 3 };
		layout.color =		{ GL_TRUE, 1, 3, 8, 3 };
		layout.uv =			{ GL_TRUE, 2, 6, 8, 2 };
		model = new Model(vertexArray, indices, layout);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model->Render();
}