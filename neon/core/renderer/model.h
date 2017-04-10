#pragma once
#include "opengl_header.h"
#include <vector>

class Model
{
	GLuint voaId = 0;
	GLuint vertexCount = 0;
	std::vector<GLuint> vbos;

	bool usingIndexBuffer = false;

	void CreateVAO();
	void CreateVBO(GLushort _location, std::vector<GLfloat> _data);
	void CreateIBO(std::vector<GLushort> _data);
	void BindVAO();
	void UnbindVAO();

public:
	Model(std::vector<GLfloat> _vertexData);
	Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices);
	virtual ~Model();

	void Render();
};	

