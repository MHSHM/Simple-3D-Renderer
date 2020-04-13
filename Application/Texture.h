#pragma once
#include <string>
class Texture
{
public:
	Texture();
	~Texture();

	bool Load(std::string path); 
	void Unload(); 

	void Bind(); 

private:
	int mWidth; 
	int mHeight; 
	unsigned int mTexture; 
};

