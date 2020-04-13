#include "pch.h"
#include "Texture.h"
#include <GL/glew.h>
#include <SDL.h>
#include <soil.h>
Texture::Texture():
	mTexture(0),
	mWidth(0),
	mHeight(0)
{
}


bool Texture::Load(std::string path) 
{
	int channels = 0; 
	unsigned char *image = SOIL_load_image(path.c_str(), &mWidth , &mHeight , &channels , SOIL_LOAD_AUTO);
	if (image == nullptr) 
	{
		SDL_Log("SOIL failed to load image %s: %s", path.c_str(), SOIL_last_result());
		return false;
	}

	int format = GL_RGB; 
	if (channels == 4) 
	{
		format = GL_RGBA; 
	}

	glGenTextures(1, &mTexture); 
	glBindTexture(GL_TEXTURE_2D , mTexture); 

	glTexImage2D(GL_TEXTURE_2D , 0 , format , mWidth , mHeight , 0 , format , GL_UNSIGNED_BYTE , image); 

	SOIL_free_image_data(image); 

	// Enable linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true; 
}

void Texture::Bind() 
{
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

void Texture::Unload() 
{
	glDeleteTextures(1, &mTexture); 
}

Texture::~Texture()
{
}
