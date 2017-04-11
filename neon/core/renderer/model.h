#pragma once
#include "opengl_header.h"
#include <vector>

struct VertexAttributeInfo
{
	GLboolean isSet = GL_FALSE;
	GLubyte locationId = 0;
	GLubyte start = 0;
	GLubyte offset = 0;
	GLubyte size = 0;
	VertexAttributeInfo() {}
	VertexAttributeInfo(GLboolean _isSet, GLubyte _locationId, GLubyte _start, GLubyte _offset, GLubyte _size):
		isSet(_isSet),
		locationId(_locationId),
		start(_start),
		offset(_offset),
		size(_size)
	{};
};
class ModelDataLayout
{
public:
	VertexAttributeInfo position;
	VertexAttributeInfo color;
	VertexAttributeInfo uv;
	VertexAttributeInfo normal;
};

class Model
{
	GLuint voaId = 0;
	GLuint vertexCount = 0;
	std::vector<GLuint> vbos;

	bool usingIndexBuffer = false;

	void CreateVAO();
	void CreateVBO(std::vector<GLfloat> _data, ModelDataLayout _layout);
	void CreateIBO(std::vector<GLushort> _data);
	void SetVertexAttribute(VertexAttributeInfo _info);
	void BindVAO();
	void UnbindVAO();

public:
	Model(std::vector<GLfloat> _vertexData);
	Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices);
	Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices, ModelDataLayout _layout);
	virtual ~Model();

	void Render();
};	

