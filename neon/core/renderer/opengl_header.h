#pragma once

#ifdef ANDROID_BUILD
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#define GLSL_VERSION_STRING		"#version 300 es\n"
#else
#define USING_GLAD 1
#include "glad\glad.h"
#define GLSL_VERSION_STRING		"#version 140\n"
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




