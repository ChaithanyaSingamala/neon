#pragma once
#include "opengl_header.h"
#include <string>
#include <vector>
#include <map>

typedef std::vector<std::pair<std::string, GLushort>> ShaderAttribInfo;

class Shader
{
	GLuint programId = 0;
	GLuint vertShaderId = 0;
	GLuint fragShaderId = 0;
	
	std::map<std::string, GLint> uniformInfos;

	bool CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	GLuint	CompileShaderCode(const GLchar *_shaderCode, GLuint _shaderType);
public:
	
	Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile);
	Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile, ShaderAttribInfo vertexAttributeLocs);
	virtual ~Shader();

	GLint GetUniformLocation(std::string _uniform);
	void UpdateUniform(std::string _uniform, GLint value);
	void Set();
	void Reset();
};

