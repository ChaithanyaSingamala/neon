#pragma once
#include "glad\glad.h"
#include <vector>
class Renderer
{
	static Renderer *instance;

	void Init();
	void DeInit();

public:
	Renderer();
	virtual ~Renderer();

	GLshort CreateVBO(std::vector<GLfloat> vertexArray);

	static Renderer *get();
	static void destroy();
};

