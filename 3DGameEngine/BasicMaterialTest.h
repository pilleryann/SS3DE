#pragma once
#ifndef BASIC_MATERIAL_TEST
#define BASIC_MATERIAL_TEST
#include "Material.h"
#include <GL\glew.h>
#include "glm\glm.hpp"
#include "TextureEngine3D.h"
#include "CubeMapTexture.h"

class BasicMaterialTest :
	public Material
{
public:
	BasicMaterialTest(GameObject * gameObject);
	BasicMaterialTest(GameObject * gameObject,std::string albedoPath,std::string normalPath);
	~BasicMaterialTest();


	 void SetMaterialToRender()override;


private :


	GLuint TextureID;
	GLuint normalMapID; 
	GLuint reflexionID;
	TextureEngine3D * m_texture;
	TextureEngine3D * m_normalsMap;
	CubeMapTexture * m_reflexion;

	std::string m_albedoPath;
	std::string m_normalPath;


protected :
	 void InitMaterialIntern() override;

};

#endif

