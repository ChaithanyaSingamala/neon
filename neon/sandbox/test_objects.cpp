#include "test_objects.h"
#include "renderer\renderer.h"
#include "engine\camera.h"
#include "renderer\model.h"
#include "renderer\shader.h"

char *ShaderCodeBaseVert()
{
	char *shaderCode =
		GLSL_VERSION_STRING
		"precision mediump float;\n"
		"in vec3 vertexPosition;								  \n"
		"in vec3 vertexColor;									  \n"
		"														  \n"
		"out vec3 vColor;										  \n"
		"														  \n"
		"void main()											  \n"
		"{														  \n"
		"	gl_Position = vec4(vertexPosition, 1.0);			  \n"
		"	vColor = vertexColor;								  \n"
		"}														  \n";

	return shaderCode;
}

char *ShaderCodeBaseFrag()
{
	char *shaderCode =
		GLSL_VERSION_STRING
		"precision mediump float;\n"
		"out vec4 fragColor;											\n"
		"in vec3 vColor;												\n"
		"																\n"
		"void main()													\n"
		"{																\n"
		"	fragColor = vec4(vColor, 1.0);								\n"
		"}																\n";

	return shaderCode;
}

char *ShaderCodeLightingVert()
{
	char *shaderCode =
	GLSL_VERSION_STRING
	"precision mediump float;\n"
	"in vec3 vertexPosition;																										  \n"
	"in vec2 vertexUV;																												  \n"
	"in vec3 vertexNormal;																											  \n"
	"																																  \n"
	"uniform mat4 model;																											  \n"
	"uniform mat4 view;																												  \n"
	"uniform mat4 proj;																												  \n"
	"uniform mat3 normalMatrix;																												  \n"
	"																																  \n"
	"out vec3 vColor;																												  \n"
	"out vec2 vUV;																													  \n"
	"																																  \n"
	"out vec3 posInWorld;																											  \n"
	"out vec3 normalInWorld;																										  \n"
	"																																  \n"
	"void main()																													  \n"
	"{																																  \n"
	"	gl_Position = proj * view * model * vec4(vertexPosition, 1.0);																  \n"
	"	vUV = vertexUV;																												  \n"
	"	posInWorld = vec3(model * vec4(vertexPosition, 1.0));																		  \n"
	"																																  \n"
	"	// assuming The normal matrix is defined as the transpose of the inverse of the upper-left corner of the model matrix		  \n"
	"	//mat3 normalMatrix = mat3(transpose(inverse(model)));																		  \n"
	"	normalInWorld = normalMatrix * vertexNormal;																				  \n"
	"}																																  \n";

	return shaderCode;
}

char *ShaderCodeLightingFrag()
{
	char *lightingFragStr =
		GLSL_VERSION_STRING
		"precision mediump float;\n"
		"out vec4 fragColor;																			\n"
		"																								\n"
		"in vec3 posInWorld;																			\n"
		"in vec3 normalInWorld;																			\n"
		"																								\n"
		"uniform vec3 objectColor;																		\n"
		"uniform vec3 lightColor;																		\n"
		"																								\n"
		"uniform vec3 lightPos;																			\n"
		"uniform vec3 viewPos;																			\n"
		"																								\n"
		"void main()																					\n"
		"{																								\n"
		"	vec3 diffuseColor = vec3(0.0);																\n"
		"	vec3 normal = normalize(normalInWorld);														\n"
		"	vec3 lightDir = normalize(lightPos - posInWorld);											\n"
		"	float diffuseFactor = max(dot(normal,lightDir), 0.0);										\n"
		"	//diffuseColor = diffuseFactor * lightColor;												\n"
		"																								\n"
		"	float specularStrength = 0.5;																\n"
		"	float shininess = 32.0;																		\n"
		"	vec3 viewDir = normalize(viewPos - posInWorld);												\n"
		"	vec3 reflectDir = reflect(lightDir, normal);												\n"
		"	float specFactor = pow(max(dot(viewDir,reflectDir), 0.0), shininess);						\n"
		"																								\n"
		"	fragColor = vec4(objectColor * (specFactor + diffuseFactor) * lightColor, 1.0);				\n"
		"}																								\n";
	return lightingFragStr;
}
Mesh * CreateModelCube(Shader *_shader)
{
	Mesh *model = 0;

	std::vector<GLfloat> vertexArray =
	{
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,							0.0f, 0.0f,
		+0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 0.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 1.0f,
		-0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 0.0f,
		+0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 0.0f,
		+0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 1.0f,
		+0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 1.0f,
		-0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 0.0f,

		-0.5f, +0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, +0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		-0.5f, -0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 0.0f,
		-0.5f,  0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 0.0f,

		+0.5f, +0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, +0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, +0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 1.0f,

		-0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 0.0f,
		-0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f

	};
	std::vector<GLushort> indices;
	for (int i = 0; i < 36; i++)
	{
		indices.push_back(36 - i - 1);
	}

	MeshDataLayout layout;
	layout.position = { GL_TRUE, _shader->GetAttribLocation(VERT_POS_LOC), 0, 8, 3 };
	layout.normal = { GL_TRUE, _shader->GetAttribLocation(VERT_NORMAL_LOC), 3, 8, 3 };
	layout.uv = { GL_TRUE, _shader->GetAttribLocation(VERT_UV0_LOC), 6, 8, 2 };
	model = new Mesh(vertexArray, indices, layout);

	return model;
}

Mesh * CreateModelPlaneXZ(Shader *_shader, float _size, float _yOffset)
{
	Mesh *model = 0;

	std::vector<GLfloat> vertexArray =
	{
		-_size, _yOffset, -_size,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f,
		+_size, _yOffset, -_size,	 0.0f,  1.0f,  0.0f,							1.0f, 1.0f,
		+_size, _yOffset, +_size,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		+_size, _yOffset, +_size,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		-_size, _yOffset, +_size,	 0.0f,  1.0f,  0.0f,							0.0f, 0.0f,
		-_size, _yOffset, -_size,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f

	};
	std::vector<GLushort> indices;
	for (int i = 0; i < 6; i++)
	{
		indices.push_back(6 - i - 1);
	}

	MeshDataLayout layout;
	layout.position = { GL_TRUE, _shader->GetAttribLocation(VERT_POS_LOC), 0, 8, 3 };
	layout.normal = { GL_TRUE, _shader->GetAttribLocation(VERT_NORMAL_LOC), 3, 8, 3 };
	layout.uv = { GL_TRUE, _shader->GetAttribLocation(VERT_UV0_LOC), 6, 8, 2 };
	model = new Mesh(vertexArray, indices, layout);

	return model;
}
