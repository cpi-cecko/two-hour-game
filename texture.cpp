#include <string>
#include <cstdlib>
#include <iostream>

#include "texture.h"
#include "stb_image.h"
#include "shader.h"

using namespace std;

texture::texture(const string& fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);
	
	if(imageData == NULL)
	{
		cout << fileName << " could not load." << endl;
		exit(EXIT_FAILURE);
	}
	
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
	stbi_image_free(imageData);
}

void texture::useTexture(unsigned short textureUnit)
{
	if(textureUnit > 16 || textureUnit < 0)
	{
		textureUnit = 0;
	}
	
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

texture::~texture()
{
	glDeleteTextures(1, &m_texture);
}
