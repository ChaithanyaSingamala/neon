#include "renderer.h"
#include "glad\glad.h"
#include "../engine/common.h"
#include <iostream>

#ifdef GLAD_DEBUG
// logs every gl call to the console
void pre_gl_call(const char *name, void *funcptr, int len_args, ...) {
	printf("Calling: %s (%d arguments)\n", name, len_args);
}
#endif


Renderer::Renderer()
{
	Init();
}

Renderer::~Renderer()
{
	DeInit();
}

GLshort Renderer::CreateVBO(std::vector<GLfloat> vertexArray)
{
	return GLshort();
}

bool Renderer::CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
		delete[] buffer;
		return false;
	}
	return true;
}
GLuint Renderer::CompileShaderCode(const GLchar * _shaderCode, GLuint _shaderType)
{
	GLuint shaderId = glCreateShader(_shaderType);
	const GLchar* code[1] = { _shaderCode };
	glShaderSource(shaderId, 1, code, 0);
	glCompileShader(shaderId);

	if (!CheckStatus(shaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS))
		ASSERT("failed to compile shader");
	return shaderId;
}

GLuint Renderer::GenerateShaderProgram(std::string _vertexShaderFile, std::string _fragmentShaderFile)
{
	std::string vertShaderCode = ReadFromFile(_vertexShaderFile);
	std::string fragShaderCode = ReadFromFile(_fragmentShaderFile);

	GLuint vertShaderId = CompileShaderCode(vertShaderCode.c_str(), GL_VERTEX_SHADER);
	GLuint fragShaderId = CompileShaderCode(fragShaderCode.c_str(), GL_FRAGMENT_SHADER);

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);
	glLinkProgram(programId);
	
	if (!CheckStatus(programId, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS))
		ASSERT("failed to compile shader");

	glUseProgram(programId);

	return programId;
}

void Renderer::Init()
{
	if (!gladLoadGL()) 
		ASSERT("GLAD failed to load!");
#ifdef GLAD_DEBUG
	glad_set_pre_callback(pre_gl_call);
	glad_debug_glClear = glad_glClear;
#endif
	//std::cout<<"OpenGL "<<GLVersion.major<<GLVersion.minor<<std::endl;
	std::cout<<"OpenGL "<<glGetString(GL_VERSION)<<", GLSL "<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

}

void Renderer::DeInit()
{
}
Renderer *Renderer::instance = nullptr;
Renderer *Renderer::get()
{
	if (!instance)
	{
		instance = new Renderer();
	}

	return instance;
}
void Renderer::destroy()
{
	if (instance)
	{
		delete instance;
	}
	instance = nullptr;
}
