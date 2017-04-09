#include <iostream>
#include "test_simpletriangle.h"
#include "glad\glad.h"

bool TestSimpleTriangle::Init()
{
	return false;
}

bool TestSimpleTriangle::Update()
{
	return false;
}

bool TestSimpleTriangle::Render()
{
	glClearColor(0.3f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return false;
}
