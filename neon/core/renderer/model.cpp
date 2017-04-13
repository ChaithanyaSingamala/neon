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
		SetVertexAttribute(_layout.position);
	if (_layout.color.isSet)
		SetVertexAttribute(_layout.color);
	if (_layout.uv.isSet)
		SetVertexAttribute(_layout.uv);
	if (_layout.normal.isSet)
		SetVertexAttribute(_layout.normal);
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

void Model::SetVertexAttribute(VertexAttributeInfo _info)
{
	glEnableVertexAttribArray(_info.locationId);
	glVertexAttribPointer(_info.locationId, _info.size, GL_FLOAT, GL_FALSE, _info.offset * sizeof(GLfloat), (void *)(_info.start * sizeof(GLfloat)));
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
	vertexCount = (GLuint)_vertexData.size();
	CreateVAO();
	ModelDataLayout layout;
	layout.position = { GL_TRUE, 0, 0, 0, 3};
	CreateVBO(_vertexData, layout);
	UnbindVAO();
}

Model::Model(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices)
{
	vertexCount = (GLuint)_indices.size();
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
	vertexCount = (GLuint)_indices.size();
	CreateVAO();
	CreateVBO(_vertexData, _layout);
	CreateIBO(_indices);
	UnbindVAO();
	usingIndexBuffer = true;
}

Model::~Model()
{
	glDeleteVertexArrays(1, &voaId);
	glDeleteBuffers((GLsizei)vbos.size(), vbos.data());
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
