#include "renderer.h"
#include "glad\glad.h"
#include "../engine/common.h"
#include <iostream>

#ifdef GLAD_DEBUG
// logs every gl call to the console
void pre_gl_call(const char *name, void *funcptr, int len_args, ...) {
	printf("Calling: %s (%d arguments)\n", name, len_args);
}
#endif


Renderer::Renderer()
{
	Init();
}

Renderer::~Renderer()
{
	DeInit();
}

GLshort Renderer::CreateVBO(std::vector<GLfloat> vertexArray)
{
	return GLshort();
}

void Renderer::Init()
{
	if (!gladLoadGL()) 
		ASSERT("GLAD failed to load!");
#ifdef GLAD_DEBUG
	glad_set_pre_callback(pre_gl_call);
	glad_debug_glClear = glad_glClear;
#endif
	//std::cout<<"OpenGL "<<GLVersion.major<<GLVersion.minor<<std::endl;
	std::cout<<"OpenGL "<<glGetString(GL_VERSION)<<", GLSL "<< glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

}

void Renderer::DeInit()
{
}

Renderer *Renderer::instance = nullptr;
Renderer *Renderer::get()
{
	if (!instance)
	{
		instance = new Renderer();
	}

	return instance;
}
void Renderer::destroy()
{
	if (instance)
	{
		delete instance;
	}
	instance = nullptr;
}
