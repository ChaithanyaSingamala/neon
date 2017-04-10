#pragma once
#include "glad\glad.h"
#include <vector>
class Renderer
{
	static Renderer *instance;

	void Init();
	void DeInit();
	bool CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	GLuint	CompileShaderCode(const GLchar *_shaderCode, GLuint _shaderType);

public:
	Renderer();
	virtual ~Renderer();

	GLshort CreateVBO(std::vector<GLfloat> vertexArray);
	GLuint	GenerateShaderProgram(std::string _vertexShaderFile, std::string _fragmentShaderFile);

	static Renderer *get();
	static void destroy();
};

