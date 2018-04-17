#pragma once
#ifndef TEXTURE_BASE
#define TEXTURE_BASE



#include <gl\glew.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class TextureBase
{
public:
	TextureBase();
	~TextureBase();

	virtual GLuint GetTexureID() = 0;


protected :
	GLuint texture_ID;
};


#endif // !TEXTURE_BASE