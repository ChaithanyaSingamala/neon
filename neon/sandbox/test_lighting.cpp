#include "test_lighting.h"
#include "renderer\renderer.h"
#include "renderer\shader.h"
//#include "renderer\texture.h"
#include "renderer\model.h"
#include "engine\orbit_camera.h"
#include "test_objects.h"
#include "engine\engine.h"

#include "glm\gtc\type_ptr.hpp"

#include <iostream>

#if 1
bool TestLighting::Init()
{
	//load camera
	camera = new OrbitCamera();
	//load texture
	//texture1 = new Texture("resources/textures/texture_4.png");

	//load shaders
	{
		shaderForLightSource = new Shader(SHADER_RESOURCE("solid.vert"), SHADER_RESOURCE("solid.frag"));
		shaderForLightSource->Set();
		shaderForLightSource->Reset();
	}
	{
		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexUV", VERT_UV0_LOC },
			{ "vertexNormal", VERT_NORMAL_LOC },
		};
		shader = new Shader(SHADER_RESOURCE("lighting01.vert"), SHADER_RESOURCE("lighting01.frag"));
		shader->Set();
		glUniform3fv(shader->GetUniformLocation("lightColor"), 1, glm::value_ptr(glm::vec3(1.0)));
		glUniform3fv(shader->GetUniformLocation("objectColor"), 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
		shader->Reset();
	}

	//load models
	testMesh = CreateModelCube(shader);
	testPlaneModel = CreateModelPlaneXZ(shader, 5.0f);

	//light source
	lightPos = glm::vec3(1.5f, 0.0f, 0.0f);
	testModelLightSource = CreateModelCube(shaderForLightSource);



	glEnable(GL_DEPTH_TEST);

	return true;
}

bool TestLighting::Render()
{
	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::vec3 newLightPos = glm::vec3(0);
	{
		static float rot = 0.0;
		rot += 1.0f * Engine::get()->GetDeltaTime();
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
		glm::mat3 normalMat = testModelLightSource->GetTransfrom();
		normalMat = glm::inverse(normalMat);
		normalMat = glm::transpose(normalMat);
		glUniformMatrix3fv(shaderForLightSource->GetUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMat));
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
			glm::mat3 normalMat = testPlaneModel->GetTransfrom();
			normalMat = glm::inverse(normalMat);
			normalMat = glm::transpose(normalMat);
			glUniformMatrix3fv(shader->GetUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMat));
			glUniformMatrix4fv(shader->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(testMesh->GetTransfrom()));
			testPlaneModel->Render();
		}

		{
			glm::mat3 normalMat = testMesh->GetTransfrom();
			normalMat = glm::inverse(normalMat);
			normalMat = glm::transpose(normalMat);
			glUniformMatrix3fv(shader->GetUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMat));
			glUniformMatrix4fv(shader->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(testMesh->GetTransfrom()));
			testMesh->Render();
		}
		
		
		shader->Reset();
	}
	return true;
}
#else
bool TestLighting::Init()
{
	return true;
}

bool TestLighting::Render()
{
	static bool init = false;
	if (!init)
	{
		Renderer* renderer = Renderer::get();
		ShaderAttribInfo infos = {
			{ "vertexPosition", VERT_POS_LOC },
			{ "vertexColor", VERT_COLOR_LOC },
		};
		//Shader *shader = new Shader(std::string("resources/shaders/v140/base.vert"), std::string("resources/shaders/v140/base.frag"), infos);
		Shader *shader = new Shader(ShaderCodeBaseVert(), ShaderCodeBaseFrag(), infos);
		shader->Set();

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

		glEnableVertexAttribArray(shader->GetAttribLocation(VERT_POS_LOC));
		glVertexAttribPointer(shader->GetAttribLocation(VERT_POS_LOC), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

		glEnableVertexAttribArray(shader->GetAttribLocation(VERT_COLOR_LOC) );
		glVertexAttribPointer(shader->GetAttribLocation(VERT_COLOR_LOC) , 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)(3 * sizeof(GLfloat)));

		init = true;

		glViewport(0, 0, 300, 300);
	}

	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	return true;
}

#endif
bool TestLighting::Update()
{
	return true;
}


bool TestLighting::DeInit()
{
	delete testMesh;
	delete shader;
	//delete texture1;

	return false;
}

void TestLighting::HandleKeyInput(int key, int action)
{
	//camera->HandleKeyInput(key, action);
	//std::cout << "key " << key << " " << action << " " << std::endl;
}

void TestLighting::HandleMouseButtonInputs(int button, int action)
{
	//camera->HandleMouseButtonInputs(button, action);
	//std::cout << "mouse button " << button << " " << action << " " << std::endl;
}

void TestLighting::HandleMouseScrollInputs(double xoffset, double yoffset)
{
	//camera->HandleMouseScrollInputs(xoffset, yoffset);
	//std::cout << "mouse scroll " << xoffset << " " << yoffset << " " << std::endl;
}

void TestLighting::HandleMouseCursorInputs(double xpos, double ypos)
{
	//camera->HandleMouseCursorInputs(xpos, ypos);
	//std::cout << "mouse cursor " << xpos << " " << ypos << " " << std::endl;
}

