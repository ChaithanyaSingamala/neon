#pragma once
#include <iostream>
#include "opengl_header.h"

class Texture
{
	GLint width;
	GLint height;
	GLuint textureId;

	static struct _staticTextureValues
	{
		GLint maxTextureUnits = -1;
		GLint maxCombinedTextureUnits = -1;
		bool init = false;
	}staticValues;

public:
	Texture(std::string _filename);
	virtual ~Texture();
	void Bind(GLint _textureUnit = UINT_MAX);
	void UnBind(GLint _textureUnit = UINT_MAX);

	static void StaticInit();
};

