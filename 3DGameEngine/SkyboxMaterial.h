#pragma once
#include "Material.h"
class GameObject;
class CubeMapTexture;
class SkyboxMaterial :
	public Material
{
public:
	SkyboxMaterial(GameObject * gameObject, CubeMapTexture * skyboxTexture);
	~SkyboxMaterial();

	void SetMaterialToRender() override;


private:
	CubeMapTexture * m_skyboxTexture;
	GLuint m_textureID;

protected :

	 void InitMaterialIntern() override;

};

