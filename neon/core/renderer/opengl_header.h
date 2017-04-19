#pragma once

#ifdef ANDROID_BUILD
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#else
#define USING_GLAD 1
#include "glad\glad.h"
#endif


// marcos
#define VERT_POS_LOC	     0
#define VERT_COLOR_LOC	     1
#define VERT_NORMAL_LOC      2
#define VERT_UV0_LOC	     3
#define VERT_UV1_LOC	     4



