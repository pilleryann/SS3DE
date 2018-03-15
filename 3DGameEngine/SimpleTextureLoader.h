#pragma once
#ifndef SIMPLE_TEXTURE_LOADER
#define SIMPLE_TEXTURE_LOADER
#include <gl\glew.h>

class SimpleTextureLoader
{
public:
	SimpleTextureLoader();
	~SimpleTextureLoader();

	static GLuint loadDDS(const char * imagepath);
};

#endif // !SIMPLE_TEXTURE_LOADER