#include <iostream>
#include "test_texturetriangle.h"
#include "renderer\renderer.h"
#include "renderer\model.h"
#include "renderer\shader.h"
#include "renderer\texture.h"
#include "interface\neon_interface.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h""

void loadModel(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	int sss = 0;
	//this->directory = path.substr(0, path.find_last_of('/'));

	//this->processNode(scene->mRootNode, scene);
}

bool TestTextureTriangle::Init()
{
	loadModel("resources/models/box.obj");
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

	testId = 1;
	switch (testId)
	{
	case 0: Test1TextureTriangle();
		break;
	case 1: Test2RotatingTextureCube();
		break;
	default: testId = 0;//not handled set to 0
		break;
	}
	

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
Shader *shader = nullptr;
glm::vec3 position(0.0f, 0.0f, 0.0f);
glm::vec3 rotation(0.0f, 0.0f, 0.0f);
glm::float32 scale = 0.6;

void UpdateModel1Transform(glm::vec3 position, glm::vec3 rotation, glm::float32 scale)
{
	glm::mat4 model1Matrix(1.0);

	model1Matrix = glm::translate(model1Matrix, position);
	model1Matrix = glm::rotate(model1Matrix, rotation.x, glm::vec3(1.0, 0.0, 0.0));
	model1Matrix = glm::rotate(model1Matrix, rotation.y, glm::vec3(0.0, 1.0, 0.0));
	model1Matrix = glm::rotate(model1Matrix, rotation.z, glm::vec3(0.0, 0.0, 1.0));
	model1Matrix = glm::scale(model1Matrix, glm::vec3(scale));

	glUniformMatrix4fv(shader->GetUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(model1Matrix));

}
void TestTextureTriangle::Test2RotatingTextureCube()
{
	static bool init = false;
	static Model *model = 0;
	
	if (!init)
	{
		glm::mat4 proj = ;

		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexUV", VERT_UV0_LOC },
			{ "vertexColor", VERT_COLOR_LOC },
		};
		Texture *texture1 = new Texture("resources/textures/texture_4.png");
		shader = new Shader("resources/shaders/v140/simpletexture.vert", "resources/shaders/v140/simpletexture.frag", infos);
		shader->Set();

		texture1->Bind(0);
		shader->UpdateUniform("Texture1", 0);
		glUniformMatrix4fv(shader->GetUniformLocation("projMatrix"), 1, GL_FALSE, glm::value_ptr(proj));

		std::vector<GLfloat> vertexArray =
		{
			-0.5f, 0.5f, 0,					0,0,
			-0.5f, -0.5f, 0,				0,1,
			0.5f, -0.5f, 0,					1,1,
			0.5f, 0.5f, 0,					1,0,
			-0.5f, 0.5f, 1,					0,0,
			-0.5f, -0.5f, 1,				0,1,
			0.5f, -0.5f, 1,					1,1,
			0.5f, 0.5f, 1,					1,0,
			0.5f, 0.5f, 0,					0,0,
			0.5f, -0.5f, 0,					0,1,
			0.5f, -0.5f, 1,					1,1,
			0.5f, 0.5f, 1,					1,0,
			-0.5f, 0.5f, 0,					0,0,
			-0.5f, -0.5f, 0,				0,1,
			-0.5f, -0.5f, 1,				1,1,
			-0.5f, 0.5f, 1,					1,0,
			-0.5f, 0.5f, 1,					0,0,
			-0.5f, 0.5f, 0,					0,1,
			0.5f, 0.5f, 0,					1,1,
			0.5f, 0.5f, 1,					1,0,
			-0.5f, -0.5f, 1,				0,0,
			-0.5f, -0.5f, 0,				0,1,
			0.5f, -0.5f, 0,					1,1,
			0.5f, -0.5f, 1,					1,0

		};
		std::vector<GLushort> indices = {
			0,1,3,
			3,1,2,
			4,5,7,
			7,5,6,
			8,9,11,
			11,9,10,
			12,13,15,
			15,13,14,
			16,17,19,
			19,17,18,
			20,21,23,
			23,21,22

		};

		ModelDataLayout layout;
		layout.position = { GL_TRUE, VERT_POS_LOC, 0, 5, 3 };
		layout.uv = { GL_TRUE, VERT_UV0_LOC, 3, 5, 2 };
		model = new Model(vertexArray, indices, layout);

		glEnable(GL_DEPTH_TEST);

		init = true;
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rotation.x += 0.0002f;
	rotation.y += 0.0002f;
	rotation.z += 0.0002f;


	UpdateModel1Transform(position, rotation, scale);
	model->Render();
}

void TestTextureTriangle::HandleKeyInput(int key, int action)
{
	if (action == 1)
	{
		switch (key)
		{
		case 262: testId++;  //right arrow key
			break;
		case 263: testId--; // left arrow key
			break;
		case 87://w
			position.z += 0.1f;
			break;
		case 83://s
			position.z -= 0.1f;
			break;

		}
	}
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
