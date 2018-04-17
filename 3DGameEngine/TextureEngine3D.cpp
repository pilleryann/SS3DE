#include "TextureEngine3D.h"
#include <iostream>
#include <SFML\Main.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>


#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII


TextureEngine3D::TextureEngine3D(const std::string path,bool isDDSTexture)
{
	if (isDDSTexture)
		texture_ID = loadDDS(path.c_str());
	else
		texture_ID = loadImage(path);
}

TextureEngine3D::~TextureEngine3D()
{
	glDeleteTexturesEXT(1, &texture_ID);
}

GLuint TextureEngine3D::GetTexureID()
{
	return texture_ID;
}


GLuint TextureEngine3D::loadDDS(const char * imagepath)
{
	//Read data part 

	unsigned char header[124];

	FILE *fp;

	fp = fopen(imagepath, "rb");
	if (fp == NULL)
		return 0;

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	//Récupère le header
	fread(&header, 124, 1, fp);



	//Recupère les informations liées au header 
	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);

	unsigned char * buffer;
	unsigned int bufsize;

	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize; 
	buffer = new unsigned char[bufsize];
	fread(buffer, 1, bufsize, fp);

	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	GLuint textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);


	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}
	delete buffer;


	return textureID;
}

GLuint TextureEngine3D::loadImage(const std::string imagePath)
{
	sf::Image imageLoaded;




	if (!imageLoaded.loadFromFile(imagePath)) {
	//	printf("Error, can't load texture : %s",imagePath);
		std::cout << "Error, can't load texture : " << imagePath << std::endl;
		return -1;
	}

	const sf::Uint8 * data = imageLoaded.getPixelsPtr();
	const sf::Vector2u imageSize = imageLoaded.getSize();

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize.x, imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbing texture 
	glBindTexture(GL_TEXTURE_2D, textureID);

	return textureID;
}
