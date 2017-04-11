#include "model.h"


void Model::CreateVAO()
{
	glGenVertexArrays(1, &voaId);
	glBindVertexArray(voaId);
}

void Model::CreateVBO(std::vector<GLfloat> _data, ModelDataLayout _layout)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _data.size() * sizeof(GLfloat), _data.data(), GL_STATIC_DRAW);
	if (_layout.position.isSet)
	{
		AttributeInfo info = _layout.position;
		glEnableVertexAttribArray(info.locationId);
		glVertexAttribPointer(info.locationId, info.size, GL_FLOAT, GL_FALSE, info.offset * sizeof(GLfloat), (void *)(info.start * sizeof(GLfloat)));
	}
	if (_layout.color.isSet)
	{
		AttributeInfo info = _layout.color;
		glEnableVertexAttribArray(info.locationId);
		glVertexAttribPointer(info.locationId, info.size, GL_FLOAT, GL_FALSE, info.offset * sizeof(GLfloat), (const void *)(info.start * sizeof(GLfloat)));
	}
	if (_layout.uv.isSet)
	{
		AttributeInfo info = _layout.uv;
		glEnableVertexAttribArray(info.locationId);
		glVertexAttribPointer(info.locationId, info.size, GL_FLOAT, GL_FALSE, info.offset * sizeof(GLfloat), (void *)(info.start * sizeof(GLfloat)));
	}
	if (_layout.normal.isSet)
	{
		AttributeInfo info = _layout.normal;
		glEnableVertexAttribArray(info.locationId);
		glVertexAttribPointer(info.locationId, info.size, GL_FLOAT, GL_FALSE, info.offset * sizeof(GLfloat), (void *)(info.start * sizeof(GLfloat)));
	}
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
	ModelDataLayout layout;
	layout.position = { GL_TRUE, 0, 0, 0, 3};
	CreateVBO(_vertexData, layout);
	UnbindVAO();
}

Model::Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices)
{
	vertexCount = _indices.size();
	CreateVAO();
	ModelDataLayout layout;
	layout.position = {GL_TRUE, 0, 0, 0, 3};
	CreateVBO(_vertexData, layout);
	CreateIBO(_indices);
	UnbindVAO();
	usingIndexBuffer = true;
}

Model::Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices, ModelDataLayout _layout)
{
	vertexCount = _indices.size();
	CreateVAO();
	CreateVBO(_vertexData, _layout);
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
