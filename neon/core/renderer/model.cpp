#include "model.h"


void Model::CreateVAO()
{
	glGenVertexArrays(1, &voaId);
	glBindVertexArray(voaId);
}

void Model::CreateVBO(GLushort _location, std::vector<GLfloat> _data)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(GLfloat), _data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	vbos.push_back(vbo);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::CreateIBO(std::vector<GLushort> _data)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _data.size() * sizeof(GLushort), _data.data(), GL_STATIC_DRAW);
	vbos.push_back(vbo);
	//if unbinding, crash happening do we need to unbind index buffer???
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Model::BindVAO()
{
	glBindVertexArray(voaId);
}

void Model::UnbindVAO()
{
	glBindVertexArray(0);
}

Model::Model(std::vector<GLfloat> _vertexData)
{
	vertexCount = _vertexData.size();
	CreateVAO();
	CreateVBO(0, _vertexData);
	UnbindVAO();
}

Model::Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices)
{
	vertexCount = _indices.size();
	CreateVAO();
	CreateVBO(0, _vertexData);
	CreateIBO(_indices);
	UnbindVAO();
	usingIndexBuffer = true;
}

Model::~Model()
{
	glDeleteVertexArrays(1, &voaId);
	glDeleteBuffers(vbos.size(), vbos.data());
}

void Model::Render()
{
	BindVAO();
	if (usingIndexBuffer)
		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_SHORT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	UnbindVAO();
}