#include "test_lighting.h"
#include "renderer\renderer.h"
#include "renderer\shader.h"
//#include "renderer\texture.h"
#include "renderer\model.h"
#include "engine\camera.h"
#include "test_objects.h"

#include "glm\gtc\type_ptr.hpp"

#include <iostream>


bool TestLighting::Init()
{
	//load camera
	camera = new Camera(glm::vec3(0.0f,0.0f,4.0f));
	//load texture
	//texture1 = new Texture("resources/textures/texture_4.png");
	//load models
	testModel = CreateModelCube();
	testPlaneModel = CreateModelPlaneXZ(5.0f);
	
	//light source
	lightPos = glm::vec3(1.5f, 0.0f, 0.0f);
	testModelLightSource = CreateModelCube();
	
	//load shaders
	{
		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
		};
//		shaderForLightSource = new Shader("resources/shaders/v140/solid.vert", "resources/shaders/v140/solid.frag", infos);
		shaderForLightSource = new Shader(ShaderCodeLightingVert(), ShaderCodeLightingFrag(), infos);
		shaderForLightSource->Set();
		shaderForLightSource->Reset();
	}
	{
		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexUV", VERT_UV0_LOC },
			{ "vertexNormal", VERT_NORMAL_LOC },
		};
//		shader = new Shader("resources/shaders/v140/lighting01.vert", "resources/shaders/v140/lighting01.frag", infos);
		shader = new Shader(ShaderCodeLightingVert(), ShaderCodeLightingFrag(), infos);
		shader->Set();
		glUniform3fv(shader->GetUniformLocation("lightColor"), 1, glm::value_ptr(glm::vec3(1.0)));
		glUniform3fv(shader->GetUniformLocation("objectColor"), 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
		shader->Reset();
	}

	glEnable(GL_DEPTH_TEST);

	return true;
}

bool TestLighting::Update()
{
	return true;
}

bool TestLighting::Render()
{
	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::vec3 newLightPos = glm::vec3(0);
	{
		static float rot = 0.0;
		rot += 0.0002f;
		shaderForLightSource->Set();
		glUniformMatrix4fv(shaderForLightSource->GetUniformLocation("proj"), 1, GL_FALSE, glm::value_ptr(camera->GetPerspectiveMatrix()));
		glUniformMatrix4fv(shaderForLightSource->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
		
		testModelLightSource->ResetTransfrom();
		testModelLightSource->Rotate(glm::vec3(0.0, 1.0, 0.0), rot);
		testModelLightSource->Translate(lightPos);
		testModelLightSource->Scale(glm::vec3(0.1f));
		glm::mat4 m = testModelLightSource->GetTransfrom();
		newLightPos.x = m[3][0];
		newLightPos.y = m[3][1];
		newLightPos.z = m[3][2];
		glUniformMatrix4fv(shaderForLightSource->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(testModelLightSource->GetTransfrom()));
		
		testModelLightSource->Render();
		shaderForLightSource->Reset();
	}

	{
		shader->Set();
		glUniformMatrix4fv(shader->GetUniformLocation("proj"), 1, GL_FALSE, glm::value_ptr(camera->GetPerspectiveMatrix()));
		glUniformMatrix4fv(shader->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
		glUniform3fv(shader->GetUniformLocation("lightPos"), 1, glm::value_ptr(newLightPos));
		glm::mat4 m = camera->GetViewMatrix();
		glm::vec3 viewPos = glm::vec3(m[3][0], m[3][1], m[3][2]);
		glUniform3fv(shader->GetUniformLocation("lightPos"), 1, glm::value_ptr(newLightPos));
	
		{
			glUniformMatrix4fv(shader->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(testModel->GetTransfrom()));
			testPlaneModel->Render();
		}

		{
			glUniformMatrix4fv(shader->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(testModel->GetTransfrom()));
			testModel->Render();
		}
		
		
		shader->Reset();
	}
	return true;
}

bool TestLighting::DeInit()
{
	delete testModel;
	delete shader;
	//delete texture1;

	return false;
}

void TestLighting::HandleKeyInput(int key, int action)
{
	camera->HandleKeyInput(key, action);
	//std::cout << "key " << key << " " << action << " " << std::endl;
}

void TestLighting::HandleMouseButtonInputs(int button, int action)
{
	camera->HandleMouseButtonInputs(button, action);
	//std::cout << "mouse button " << button << " " << action << " " << std::endl;
}

void TestLighting::HandleMouseScrollInputs(double xoffset, double yoffset)
{
	camera->HandleMouseScrollInputs(xoffset, yoffset);
	//std::cout << "mouse scroll " << xoffset << " " << yoffset << " " << std::endl;
}

void TestLighting::HandleMouseCursorInputs(double xpos, double ypos)
{
	camera->HandleMouseCursorInputs(xpos, ypos);
	//std::cout << "mouse cursor " << xpos << " " << ypos << " " << std::endl;
}

