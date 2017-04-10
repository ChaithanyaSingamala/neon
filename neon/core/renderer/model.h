#pragma once
#include "opengl_header.h"
#include <vector>

class Model
{
	GLuint voaId = 0;
	GLuint vertexCount = 0;
	std::vector<GLuint> vbos;

	void CreateVAO();
	void CreateVBO(GLushort _location, std::vector<GLfloat> _data);
	void BindVAO();
	void UnbindVAO();

public:
	Model(std::vector<GLfloat> _vertexData);
	virtual ~Model();

	void Render();
};	

