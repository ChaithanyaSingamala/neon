#include "shader.h"
#include "../engine/common.h"
#include <iostream>

Shader::Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile)
{
	std::string vertShaderCode = ReadFromFile(_vertexShaderFile);
	std::string fragShaderCode = ReadFromFile(_fragmentShaderFile);

	vertShaderId = CompileShaderCode(vertShaderCode.c_str(), GL_VERTEX_SHADER);
	fragShaderId = CompileShaderCode(fragShaderCode.c_str(), GL_FRAGMENT_SHADER);

	programId = glCreateProgram();
	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);
	glLinkProgram(programId);

	if (!CheckStatus(programId, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS))
		ASSERT("failed to compile shader");

}

Shader::~Shader()
{
	UnBind();
	glDetachShader(programId, vertShaderId);
	glDetachShader(programId, fragShaderId);
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);
	glDeleteProgram(programId);
	programId = 0;
	vertShaderId = 0;
	fragShaderId = 0;
}

void Shader::BindAttributeLocation(std::string _attributeName, GLuint _location)
{
	glBindAttribLocation(programId, _location, _attributeName.c_str());
}

void Shader::Bind()
{
	glUseProgram(programId);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

bool Shader::CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType)
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
GLuint Shader::CompileShaderCode(const GLchar * _shaderCode, GLuint _shaderType)
{
	GLuint shaderId = glCreateShader(_shaderType);
	const GLchar* code[1] = { _shaderCode };
	glShaderSource(shaderId, 1, code, 0);
	glCompileShader(shaderId);

	if (!CheckStatus(shaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS))
		ASSERT("failed to compile shader");
	return shaderId;
}