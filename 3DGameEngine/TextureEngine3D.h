#pragma once
#ifndef TEXTURE_ENGINE_3D
#define TEXTURE_ENGINE_3D
#include "TextureBase.h"

class TextureEngine3D : TextureBase
{
public:
	TextureEngine3D(std::string path,bool isDDSTexture=false);
	~TextureEngine3D();

	GLuint GetTexureID();

private :
	GLuint loadPng(std::string pngPath);
	GLuint loadDDS(const char * imagepath);
	GLuint loadImage(const std::string imagePath);
};

#endif // !TEXTURE_ENGINE_3D