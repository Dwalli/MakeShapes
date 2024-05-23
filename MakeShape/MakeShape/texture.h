#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class Texture
{
public:
	GLuint textureID; // ID for the Texture
	Texture(const char* image, GLenum textureChanel, GLenum textureType, GLenum imageFormat, GLenum pixelType = GL_UNSIGNED_BYTE, GLenum scaleType = GL_NEAREST);

	void LinkTexture(const char* uniform, Shader& shader, GLuint unit);
	void BindTexture();
	void UnBindTexture();
	void OnDelete();

private:
	GLenum texType;
};


#endif // !VBH_H#pragma once
