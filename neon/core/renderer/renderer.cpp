#include "renderer.h"
#include "../engine/common.h"
#include <iostream>
#include <string>
#include <sstream>
#include "interface\neon_interface.h"

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

void Renderer::SetViewport(GLushort x, GLushort y, GLushort width, GLushort height)
{
	if (width == 0)
		width = NeonInterface::get()->Width();
	if (height == 0)
		height = NeonInterface::get()->Height();
#if ENABLE_DEBUG > 3
	if (width > NeonInterface::get()->Width() || height > NeonInterface::get()->Height())
		ASSERT("setting viewport greater than window size");
	if (x != 0 || y != 0)
		if ((width - x < 0) || (height - y < 0))
			ASSERT("setting viewport x,y making viewport smaller than 0");
#endif
	glViewport(x, y, width, height);

}

void Renderer::Init()
{
#if USING_GLAD
	if (!gladLoadGL()) 
		ASSERT("GLAD failed to load!");
#endif
#ifdef GLAD_DEBUG
	glad_set_pre_callback(pre_gl_call);
	glad_debug_glClear = glad_glClear;
#endif
	
	/* Query OpenGL device information */
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	std::stringstream ss;
	ss << "\n-------------------------------------------------------------\n";
	ss << "GL Vendor    : " << vendor;
	ss << "\nGL GLRenderer : " << renderer;
	ss << "\nGL Version   : " << version;
	ss << "\nGL Version   : " << major << "." << minor;
	ss << "\nGLSL Version : " << glslVersion;
	ss << "\n-------------------------------------------------------------\n";
	printf("%s", ss.str().c_str());

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
