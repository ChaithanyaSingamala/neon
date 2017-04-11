#pragma once
#include "opengl_header.h"
#include <vector>
class Renderer
{
	static Renderer *instance;

	void Init();
	void DeInit();

public:
	Renderer();
	virtual ~Renderer();

	void SetViewport(GLushort x = 0, GLushort y = 0, GLushort width = 0, GLushort height = 0);

	static Renderer *get();
	static void destroy();
};

