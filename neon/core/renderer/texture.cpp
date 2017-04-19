#include "texture.h"
#ifndef ANDROID_BUILD
#include "SOIL.h"
#endif
struct Texture::_staticTextureValues Texture::staticValues;

Texture::Texture(std::string _filename)
{
	if (!staticValues.init)
		StaticInit();
	unsigned char* image;
#ifndef ANDROID_BUILD
	image = SOIL_load_image(_filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
#endif
	glGenTextures(1, &textureId);
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
#ifndef ANDROID_BUILD
	SOIL_free_image_data(image);
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	UnBind();
}


Texture::~Texture()
{
	UnBind();
	glDeleteTextures(1, &textureId);

}

void Texture::Bind(GLint _textureUnit)
{
	if (_textureUnit < staticValues.maxCombinedTextureUnits)
		glActiveTexture(GL_TEXTURE0 + _textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::UnBind(GLint _textureUnit)
{
	glBindTexture(GL_TEXTURE_2D, 0);
	if (_textureUnit < staticValues.maxCombinedTextureUnits)
		glActiveTexture(0);

}

void Texture::StaticInit()
{
	//GL_MAX_CUBE_MAP_TEXTURE_SIZE
	//GL_MAX_TEXTURE_SIZE
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &staticValues.maxTextureUnits);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &staticValues.maxCombinedTextureUnits);
	staticValues.init = true;
}
