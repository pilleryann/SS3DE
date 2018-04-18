#include "CubeMapTexture.h"
#include <SFML\Graphics.hpp>



CubeMapTexture::CubeMapTexture() : CubeMapTexture("Datas/SkyBox/right.jpg", "Datas/SkyBox/left.jpg", "Datas/SkyBox/top.jpg", "Datas/SkyBox/bottom.jpg","Datas/SkyBox/front.jpg","Datas/SkyBox/back.jpg")
{
	
}

CubeMapTexture::CubeMapTexture(std::string rightPath, std::string leftPath, std::string topPath, std::string bottomPath, std::string frontPath, std::string backPath)
{
	std::string faces[6] = { rightPath,leftPath,topPath,bottomPath,frontPath,backPath};

	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_ID);
	for (unsigned int i = 0; i < 6; i++) {
		
		sf::Image imageLoaded;

		if (!imageLoaded.loadFromFile(faces[i])) {
			//	printf("Error, can't load texture : %s",imagePath);
			std::cout << "Error, can't load texture : " << faces[i] << std::endl;
			return;
		}

		const sf::Uint8 * data = imageLoaded.getPixelsPtr();
		const sf::Vector2u imageSize = imageLoaded.getSize();
		
		/*
		GL_TEXTURE_CUBE_MAP_POSITIVE_X ->	Right
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X ->	Left
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y ->	Top
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y ->	Bottom
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z ->	Back
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z ->	Front
		
		*/
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, GL_RGBA, imageSize.x, imageSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//glBindTexture(GL_TEXTURE_CUBE_MAP,0);

} 

CubeMapTexture::~CubeMapTexture()
{
}

GLuint CubeMapTexture::GetTexureID()
{
	return texture_ID;
}
