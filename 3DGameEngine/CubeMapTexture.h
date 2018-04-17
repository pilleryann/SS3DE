#pragma once
#include "TextureBase.h"
class CubeMapTexture :
	public TextureBase
{
public:
	CubeMapTexture();
	CubeMapTexture(std::string rightPath, std::string leftPath, std::string topPath, std::string bottomPath,std::string frontPath,std::string backPath);
	~CubeMapTexture();

	GLuint GetTexureID() override;



};

