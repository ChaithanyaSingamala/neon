#pragma once
#include "opengl_header.h"
#include <string>

class Shader
{
	GLuint programId = 0;
	GLuint vertShaderId = 0;
	GLuint fragShaderId = 0;
	
	bool CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	GLuint	CompileShaderCode(const GLchar *_shaderCode, GLuint _shaderType);

public:
	Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile);
	virtual ~Shader();

	void BindAttributeLocation(std::string _attributeName, GLuint _location);

	void Bind();
	void UnBind();
};

