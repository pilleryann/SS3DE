#pragma once
#ifndef TEXTURE_ENGINE_3D
#define TEXTURE_ENGINE_3D
#include <gl\glew.h>
#include <string>

class TextureEngine3D
{
public:
	TextureEngine3D(std::string path,bool isDDSTexture=false);
	~TextureEngine3D();

	GLuint GetTexureID();

private :
	GLuint texture_ID;

	GLuint loadDDS(const char * imagepath);
	GLuint loadImage(const std::string imagePath);
};

#endif // !TEXTURE_ENGINE_3D