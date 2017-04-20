#include "shader.h"
#include "../engine/common.h"
#include <iostream>

Shader::Shader()
{

}

Shader::Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile, ShaderAttribInfo _vertexAttributeLocs)
{
	std::string vertShaderCode = ReadFromFile(_vertexShaderFile);
	std::string fragShaderCode = ReadFromFile(_fragmentShaderFile);

	CompileShaderCode(vertShaderCode, fragShaderCode);
	InitAttribLocations(_vertexAttributeLocs);
}

Shader::Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile)
{
	std::string vertShaderCode = ReadFromFile(_vertexShaderFile);
	std::string fragShaderCode = ReadFromFile(_fragmentShaderFile);

	CompileShaderCode(vertShaderCode, fragShaderCode);

	ShaderAttribInfo vertexAttributeLocs = {
		{ "vertexPosition", VERT_POS_LOC },
		{ "vertexColor", VERT_COLOR_LOC },
		{ "vertexNormal", VERT_NORMAL_LOC },
		{ "vertexUV", VERT_UV0_LOC },
		{ "vertexUV1", VERT_UV1_LOC },
	};

	InitAttribLocations(vertexAttributeLocs);
}

void Shader::CompileShaderCode(std::string _shaderCodeVert, std::string _shaderCodeFrag)
{
	vertShaderId = CompileShaderCode(_shaderCodeVert, GL_VERTEX_SHADER);
	fragShaderId = CompileShaderCode(_shaderCodeFrag, GL_FRAGMENT_SHADER);

	programId = glCreateProgram();
	glAttachShader(programId, vertShaderId);
	glAttachShader(programId, fragShaderId);

	glLinkProgram(programId);

	CheckStatus(programId, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

void Shader::InitAttribLocations(ShaderAttribInfo _vertexAttributeLocs)
{
	for (auto info : _vertexAttributeLocs)
		attrribLocations[info.second] = glGetAttribLocation(programId, info.first.c_str());
}

Shader::~Shader()
{
	Reset();
	glDetachShader(programId, vertShaderId);
	glDetachShader(programId, fragShaderId);
	glDeleteShader(vertShaderId);
	glDeleteShader(fragShaderId);
	glDeleteProgram(programId);
	programId = 0;
	vertShaderId = 0;
	fragShaderId = 0;
}

GLint Shader::GetUniformLocation(std::string _uniform)
{
	GLint locPlusOne = uniformInfos[_uniform.c_str()];
	if (locPlusOne == 0)
		locPlusOne = uniformInfos[_uniform.c_str()] = glGetUniformLocation(programId, _uniform.c_str()) + 1;
	return locPlusOne - 1;
}

GLint Shader::GetAttribLocation(GLint _attrib)
{
	return attrribLocations[_attrib];
}


void Shader::UpdateUniform(std::string _uniform, GLint value)
{
	glUniform1i(GetUniformLocation(_uniform), value);
}

void Shader::Set()
{
	glUseProgram(programId);
}

void Shader::Reset()
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
		LOG("%s", buffer);
		ASSERT("failed in compile shader");
		delete[] buffer;
		return false;
	}
	return true;
}
GLuint Shader::CompileShaderCode(std::string _shaderCode, GLuint _shaderType)
{
	GLuint shaderId = glCreateShader(_shaderType);
	const GLchar* code[1] = { _shaderCode.c_str() };
	glShaderSource(shaderId, 1, code, 0);
	glCompileShader(shaderId);

	CheckStatus(shaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);

	return shaderId;
}