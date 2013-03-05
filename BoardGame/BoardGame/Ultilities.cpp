#include "Ultilities.h"
#include <iostream>

bool LoadTextures(char **textureFiles, GLuint *hTexture, GLint numTextures)
{
	glGenTextures(numTextures, hTexture);
	//initialize each texture seperately
	GLint width, height, components;
	GLenum eFormat;
	GLbyte *buffer;
	for(int i = 0; i < numTextures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, hTexture[i]);
		buffer = gltReadTGABits(textureFiles[i], &width, &height, &components, &eFormat);
		if(buffer == NULL)
		{
			std::cout << "Cannot load file " << textureFiles[i];
			return false;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, eFormat, GL_UNSIGNED_BYTE, buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		free(buffer);	//don't need to buffer anymore
	}

	return true;
}

bool LoadTextures(char *textureFile, GLuint *hTexture)
{
	GLint width, height, components;
	GLenum eFormat;
	GLbyte *buffer;

	glGenTextures(1, hTexture);
	buffer = gltReadTGABits(textureFile, &width, &height, &components, &eFormat);
	if(!buffer)
	{
		std::cout << "Cannot load file " << textureFile;
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, components, width, height, 0, eFormat, GL_UNSIGNED_BYTE, buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	free(buffer);	//don't need to buffer anymore
	return true;
}
