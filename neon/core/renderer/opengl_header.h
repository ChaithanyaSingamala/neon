#pragma once

#ifdef ANDROID_BUILD
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#define GLSL_VERSION_STRING		"#version 300 es\n"
#define GLSL_VERSION			"v300es"
#else
#define USING_GLAD 1
#include "glad\glad.h"
#define GLSL_VERSION_STRING		"#version 140\n"
#define GLSL_VERSION			"v140"
#endif

#ifndef USING_GLAD
typedef void (* PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
typedef void (* PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
#endif


enum
{
	VERT_POS_LOC = 0,
	VERT_COLOR_LOC,
	VERT_NORMAL_LOC,
	VERT_UV0_LOC,
	VERT_UV1_LOC,

	VERT_ATTRIB_MAX
};




