#pragma once
#include "engine\defines.h"
#include <string>
#include <vector>
#include <map>

#define SHADER_RES_DIR	"shaders/"
#define SHADER_RESOURCE(x)		RESOURCES_PATH SHADER_RES_DIR GLSL_VERSION PATH_SEPRATER x


typedef std::vector<std::pair<std::string, GLushort>> ShaderAttribInfo;

class Shader
{
	GLuint programId = 0;
	GLuint vertShaderId = 0;
	GLuint fragShaderId = 0;
	
	std::map<std::string, GLint> uniformInfos;

	GLint attrribLocations[VERT_ATTRIB_MAX];

	bool CheckStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetterFunc, PFNGLGETSHADERINFOLOGPROC getInfoLogFunc, GLenum statusType);
	GLuint	CompileShaderCode(std::string _shaderCode, GLuint _shaderType);
public:
	
	Shader();
	Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile, ShaderAttribInfo vertexAttributeLocs);
	Shader(std::string _vertexShaderFile, std::string _fragmentShaderFile);
	virtual ~Shader();

	void CompileShaderCode(std::string _shaderCodeVert, std::string _shaderCodeFrag);
	void InitAttribLocations(ShaderAttribInfo _vertexAttributeLocs);

	GLint GetUniformLocation(std::string _uniform);
	GLint GetAttribLocation(GLint _attrib);
	void UpdateUniform(std::string _uniform, GLint value);
	void Set();
	void Reset();
};

