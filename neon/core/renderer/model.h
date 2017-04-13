#pragma once
#include "opengl_header.h"
#include <vector>
#include "glm\glm.hpp"

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

	glm::mat4 transform = glm::mat4(1);

public:
	Model(std::vector<GLfloat> _vertexData);
	Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices);
	Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices, ModelDataLayout _layout);
	virtual ~Model();

	void SetTransformation(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
	void Translate(glm::vec3 _pos);
	void Rotate(glm::vec3 _axis, glm::float32 angle);
	void Scale(glm::vec3 _scale);

	glm::mat4 GetTransfrom();
	void ResetTransfrom();

	void Render();
};	

