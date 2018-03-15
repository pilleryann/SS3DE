#pragma once
#ifndef BASIC_MATERIAL_TEST
#define BASIC_MATERIAL_TEST
#include "Material.h"
#include <GL\glew.h>
#include "glm\glm.hpp"
#include "TextureEngine3D.h"

class BasicMaterialTest :
	public Material
{
public:
	BasicMaterialTest(GameObject * gameObject);
	~BasicMaterialTest();


	 void SetMaterialToRender()override;


private :

	GLuint lightWorldPosition_ID ;
	GLuint lightColor_ID ;
	GLuint lightPower_ID ;
	GLuint TextureID;
	TextureEngine3D * m_texture;

	float lightPower;
	glm::vec3 lightColor;
	glm::vec3 lightPosition;
protected :
	 void InitMaterialIntern() override;

};

#endif

