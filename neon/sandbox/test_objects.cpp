#include "test_objects.h"
#include "renderer\renderer.h"
#include "engine\camera.h"
#include "renderer\model.h"

Model * CreateModelCube()
{
	Model *model = 0;

	std::vector<GLfloat> vertexArray =
	{
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,							0.0f, 0.0f,
		+0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 0.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							1.0f, 1.0f,
		-0.5f, +0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f, 							0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 0.0f,
		+0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 0.0f,
		+0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 1.0f,
		+0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								1.0f, 1.0f,
		-0.5f, +0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f, 1.0f,								0.0f, 0.0f,

		-0.5f, +0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, +0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		-0.5f, -0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							0.0f, 0.0f,
		-0.5f,  0.5f, +0.5f,	-1.0f,  0.0f,  0.0f,							1.0f, 0.0f,

		+0.5f, +0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, +0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, +0.5f,	 1.0f,  0.0f,  0.0f,							0.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,	 1.0f,  0.0f,  0.0f,							1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, -0.5f, +0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,							0.0f, 1.0f,

		-0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 1.0f,
		+0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		-0.5f, +0.5f, +0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 0.0f,
		-0.5f, +0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f

	};
	std::vector<GLushort> indices;
	for (int i = 0; i < 36; i++)
	{
		indices.push_back(36 - i - 1);
	}

	ModelDataLayout layout;
	layout.position = { GL_TRUE, VERT_POS_LOC, 0, 8, 3 };
	layout.normal = { GL_TRUE, VERT_NORMAL_LOC, 3, 8, 3 };
	layout.uv = { GL_TRUE, VERT_UV0_LOC, 6, 8, 2 };
	model = new Model(vertexArray, indices, layout);

	return model;
}

Model * CreateModelPlaneXZ(float _size, float _yOffset)
{
	Model *model = 0;

	std::vector<GLfloat> vertexArray =
	{
		-_size, _yOffset, -_size,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f,
		+_size, _yOffset, -_size,	 0.0f,  1.0f,  0.0f,							1.0f, 1.0f,
		+_size, _yOffset, +_size,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		+_size, _yOffset, +_size,	 0.0f,  1.0f,  0.0f,							1.0f, 0.0f,
		-_size, _yOffset, +_size,	 0.0f,  1.0f,  0.0f,							0.0f, 0.0f,
		-_size, _yOffset, -_size,	 0.0f,  1.0f,  0.0f,							0.0f, 1.0f

	};
	std::vector<GLushort> indices;
	for (int i = 0; i < 6; i++)
	{
		indices.push_back(6 - i - 1);
	}

	ModelDataLayout layout;
	layout.position = { GL_TRUE, VERT_POS_LOC, 0, 8, 3 };
	layout.normal = { GL_TRUE, VERT_NORMAL_LOC, 3, 8, 3 };
	layout.uv = { GL_TRUE, VERT_UV0_LOC, 6, 8, 2 };
	model = new Model(vertexArray, indices, layout);

	return model;
}
