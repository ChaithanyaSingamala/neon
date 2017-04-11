#include <iostream>
#include "test_texturetriangle.h"
#include "renderer\renderer.h"
#include "renderer\model.h"
#include "renderer\shader.h"
#include "renderer\texture.h"

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


void TestTextureTriangle::Test1TextureTriangle()
{
	static bool init = false;
	static Model *model = 0;
	if (!init)
	{

		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexUV", VERT_UV0_LOC },
			{ "vertexColor", VERT_COLOR_LOC },
		};
		Texture *texture1 = new Texture("resources/textures/texture_4.png");
		Texture *texture2 = new Texture("resources/textures/checks.png");
		Shader *shader = new Shader("resources/shaders/v140/simpletexture.vert", "resources/shaders/v140/simple_multitexture.frag", infos);
		shader->Set(); 

		texture1->Bind(0);
		texture2->Bind(1);
		shader->UpdateUniform("Texture1", 0);
		shader->UpdateUniform("Texture2", 1);

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
		layout.position =	{ GL_TRUE, VERT_POS_LOC, 0, 8, 3 };
		layout.color =		{ GL_TRUE, VERT_COLOR_LOC, 3, 8, 3 };
		layout.uv =			{ GL_TRUE, VERT_UV0_LOC, 6, 8, 2 };
		model = new Model(vertexArray, indices, layout);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model->Render();
}

void TestTextureTriangle::HandleKeyInput(int key, int action)
{
	//std::cout << "key " << key << " " << action << " " << std::endl;
}

void TestTextureTriangle::HandleMouseButtonInputs(int button, int action)
{
	//std::cout << "mouse button " << button << " " << action << " " << std::endl;
}

void TestTextureTriangle::HandleMouseScrollInputs(double xoffset, double yoffset)
{
	//std::cout << "mouse scroll " << xoffset << " " << yoffset << " " << std::endl;
}

void TestTextureTriangle::HandleMouseCursorInputs(double xpos, double ypos)
{
	//std::cout << "mouse cursor " << xpos << " " << ypos << " " << std::endl;
}
