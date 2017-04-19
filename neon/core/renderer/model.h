#pragma once
#include "opengl_header.h"
#include <vector>
#include <iostream>
#include "glm\glm.hpp"

#ifndef ANDROID_BUILD
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#endif

struct VertexAttributeInfo
{
	GLboolean isSet = GL_FALSE;
	GLint locationId = 0;
	GLubyte start = 0;
	GLubyte offset = 0;
	GLubyte size = 0;
	VertexAttributeInfo() {}
	VertexAttributeInfo(GLboolean _isSet, GLint _locationId, GLubyte _start, GLubyte _offset, GLubyte _size):
		isSet(_isSet),
		locationId(_locationId),
		start(_start),
		offset(_offset),
		size(_size)
	{};
};
class MeshDataLayout
{
public:
	VertexAttributeInfo position;
	VertexAttributeInfo color;
	VertexAttributeInfo uv;
	VertexAttributeInfo normal;
};

class Mesh;

class Model
{
	std::vector<Mesh*> meshes;
	std::string directory;

	glm::mat4 transform = glm::mat4(1);

public:
	Model(std::string _fileName);
#ifndef ANDROID_BUILD
    void ProcessNode(aiNode * node, const aiScene * scene);
	Mesh* ProcessMesh(aiMesh * mesh, const aiScene * scene);
#endif
    virtual ~Model();

	Mesh* GetMesh(int index);

	void SetTransformation(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
	void Translate(glm::vec3 _pos);
	void Rotate(glm::vec3 _axis, glm::float32 angle);
	void Scale(glm::vec3 _scale);

	glm::mat4 GetTransfrom();
	void ResetTransfrom();

	void Render();
};

class Mesh
{
	GLuint voaId = 0;
	GLuint vertexCount = 0;
	std::vector<GLuint> vbos;

	bool usingIndexBuffer = false;

	void CreateVAO();
	void CreateVBO(std::vector<GLfloat> _data, MeshDataLayout _layout);
	void CreateIBO(std::vector<GLushort> _data);
	void SetVertexAttribute(VertexAttributeInfo _info);
	void BindVAO();
	void UnbindVAO();

	glm::mat4 transform = glm::mat4(1);

public:
	Mesh(std::vector<GLfloat> _vertexData);
	Mesh(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices);
	Mesh(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices, MeshDataLayout _layout);
	virtual ~Mesh();

	void SetTransformation(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
	void Translate(glm::vec3 _pos);
	void Rotate(glm::vec3 _axis, glm::float32 angle);
	void Scale(glm::vec3 _scale);

	glm::mat4 GetTransfrom();
	void ResetTransfrom();

	void Render();
};	

