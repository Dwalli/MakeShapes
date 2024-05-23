#include "texture.h"

Texture::Texture(const char* image, GLenum textureChanel, GLenum textureType, GLenum imageFormat, GLenum pixelType , GLenum scaleType)
{
	texType = textureType;

	int imageWidth, imageHight, noColorChanels;
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &imageWidth, &imageHight, &noColorChanels, 0);

	glGenTextures(1, &textureID);
	glActiveTexture(textureChanel);
	glBindTexture(textureType, textureID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, scaleType);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, scaleType);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(textureType, 0, imageFormat, imageWidth, imageWidth, 0, imageFormat, pixelType, bytes);
	glGenerateMipmap(textureType);

	stbi_image_free(bytes);
	glBindTexture(textureType, 0);


}

void Texture::LinkTexture(const char* uniform, Shader& shader, GLuint unit)
{
	// Gets the location of the uniform
	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
	shader.OnActivate();
	glUniform1i(tex0Uni, unit);
}

void Texture::BindTexture()
{
	glBindTexture(texType, textureID);
}

void Texture::UnBindTexture()
{
	glBindTexture(texType, 0);
}

void Texture::OnDelete()
{
	glDeleteTextures(1, &textureID);
}


