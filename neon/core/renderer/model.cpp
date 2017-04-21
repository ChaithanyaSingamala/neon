#include "model.h"
#include "engine\common.h"
#include "engine\defines.h"
#include "glm\gtc\matrix_transform.hpp"

bool Mesh::isGlobalWireFrame = false;

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &voaId);
	glBindVertexArray(voaId);
}

void Mesh::CreateVBO(std::vector<GLfloat> _data, MeshDataLayout _layout)
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

void Mesh::CreateIBO(std::vector<GLushort> _data)
{
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _data.size() * sizeof(GLushort), _data.data(), GL_STATIC_DRAW);
	vbos.push_back(vbo);
	//if unbinding, crash happening do we need to unbind index buffer???
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::SetVertexAttribute(VertexAttributeInfo _info)
{
	glEnableVertexAttribArray(_info.locationId);
	glVertexAttribPointer(_info.locationId, _info.size, GL_FLOAT, GL_FALSE, _info.offset * sizeof(GLfloat), (void *)(_info.start * sizeof(GLfloat)));
}

void Mesh::BindVAO()
{
	glBindVertexArray(voaId);
}

void Mesh::UnbindVAO()
{
	glBindVertexArray(0);
}

Mesh::Mesh(std::vector<GLfloat> _vertexData)
{
	vertexCount = (GLuint)_vertexData.size();
	CreateVAO();
	MeshDataLayout layout;
	layout.position = { GL_TRUE, 0, 0, 0, 3};
	CreateVBO(_vertexData, layout);
	UnbindVAO();
}

Mesh::Mesh(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices)
{
	vertexCount = (GLuint)_indices.size();
	CreateVAO();
	MeshDataLayout layout;
	layout.position = {GL_TRUE, 0, 0, 0, 3};
	CreateVBO(_vertexData, layout);
	CreateIBO(_indices);
	UnbindVAO();
	usingIndexBuffer = true;
}

Mesh::Mesh(std::vector<GLfloat> _vertexData, std::vector<GLushort> _indices, MeshDataLayout _layout)
{
	vertexCount = (GLuint)_indices.size();
	CreateVAO();
	CreateVBO(_vertexData, _layout);
	CreateIBO(_indices);
	UnbindVAO();
	usingIndexBuffer = true;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &voaId);
	glDeleteBuffers((GLsizei)vbos.size(), vbos.data());
}

void Mesh::SetGlobalWireFrame(bool _value)
{
	isGlobalWireFrame = true;
}

void Mesh::SetWireFrame(bool _value)
{
	isWireFrame = _value;
}

void Mesh::SetTransformation(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
{
	transform = glm::mat4(1);

	transform = glm::translate(transform, _pos);
	transform = glm::rotate(transform, _rot.x, glm::vec3(1.0, 0.0, 0.0));
	transform = glm::rotate(transform, _rot.y, glm::vec3(0.0, 1.0, 0.0));
	transform = glm::rotate(transform, _rot.z, glm::vec3(0.0, 0.0, 1.0));
	transform = glm::scale(transform, glm::vec3(_scale));

}

void Mesh::Translate(glm::vec3 _pos)
{
	transform = glm::translate(transform, _pos);
}

void Mesh::Rotate(glm::vec3 _axis, glm::float32 angle)
{
	transform = glm::rotate(transform, angle, _axis);
}

void Mesh::Scale(glm::vec3 _scale)
{
	transform = glm::scale(transform, glm::vec3(_scale));
}

glm::mat4 Mesh::GetTransfrom()
{
	return transform;
}

void Mesh::ResetTransfrom()
{
	transform = glm::mat4(1);
}

void Mesh::Render()
{
	BindVAO();
#ifdef GL_POLYMODE_SUPPORT
	if(isGlobalWireFrame || isWireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
if (usingIndexBuffer)
		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_SHORT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, vertexCount);
#ifdef GL_POLYMODE_SUPPORT
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
	UnbindVAO();
}

Model::Model(std::string _fileName)
{
#ifndef ANDROID_BUILD
    Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_fileName, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::string error = importer.GetErrorString();
		ASSERT("ERROR::ASSIMP");
		return;
	}
	directory = _fileName.substr(0, _fileName.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
#endif
}
#ifndef ANDROID_BUILD
void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(ProcessMesh(mesh, scene));
	}
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}

}

Mesh *Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<GLushort> indices;
	//vector<Texture> textures;

	int totalVertexLength = 8;
	std::vector<GLfloat> vertices(mesh->mNumVertices * totalVertexLength);

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		vertices[0 + i * 8] =  mesh->mVertices[i].x;
		vertices[1 + i * 8] = mesh->mVertices[i].y;
		vertices[2 + i * 8] = mesh->mVertices[i].z;
		// Normals
		if (mesh->mNormals)
		{
			vertices[3 + i * 8] = mesh->mNormals[i].x;
			vertices[4 + i * 8] = mesh->mNormals[i].y;
			vertices[5 + i * 8] = mesh->mNormals[i].z;
		}
		else
		{
			vertices[3 + i * 8] = 0.0f;
			vertices[4 + i * 8] = 0.0f;
			vertices[5 + i * 8] = 0.0f;
		}

		if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			vertices[6 + i * 8] = mesh->mTextureCoords[0][i].x;
			vertices[7 + i * 8] = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertices[6 + i * 8] = 0.0f;
			vertices[7 + i * 8] = 0.0f;
		}
	}
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	/** /
	// Process materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	*/
	MeshDataLayout layout;
	layout.position = { GL_TRUE, VERT_POS_LOC, 0, 8, 3 };
	layout.normal = { GL_TRUE, VERT_NORMAL_LOC, 3, 8, 3 };
	layout.uv = { GL_TRUE, VERT_UV0_LOC, 6, 8, 2 };

	return new Mesh(vertices, indices, layout);
}
#endif
void Model::SetTransformation(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
{
	transform = glm::mat4(1);

	transform = glm::translate(transform, _pos);
	transform = glm::rotate(transform, _rot.x, glm::vec3(1.0, 0.0, 0.0));
	transform = glm::rotate(transform, _rot.y, glm::vec3(0.0, 1.0, 0.0));
	transform = glm::rotate(transform, _rot.z, glm::vec3(0.0, 0.0, 1.0));
	transform = glm::scale(transform, glm::vec3(_scale));

}

void Model::Translate(glm::vec3 _pos)
{
	transform = glm::translate(transform, _pos);
}

void Model::Rotate(glm::vec3 _axis, glm::float32 angle)
{
	transform = glm::rotate(transform, angle, _axis);
}

void Model::Scale(glm::vec3 _scale)
{
	transform = glm::scale(transform, glm::vec3(_scale));
}

glm::mat4 Model::GetTransfrom()
{
	return transform;
}

void Model::ResetTransfrom()
{
	transform = glm::mat4(1);
}

void Model::Render()
{
	for (auto mesh : meshes)
		mesh->Render();
}



Model::~Model()
{
}

Mesh * Model::GetMesh(int index)
{
	if (index < meshes.size())
		return meshes[index];
	return nullptr;
}
