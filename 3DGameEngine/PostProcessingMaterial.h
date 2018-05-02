#pragma once
#include "Material.h"
#include "TextureCamera.h"
class PostProcessingMaterial :
	public Material
{
public:
	PostProcessingMaterial(GameObject * gameObject,TextureCamera * textureCamera);
	~PostProcessingMaterial();

	 void SetMaterialToRender() override;
protected:
	void InitMaterialIntern() override;

private :

	TextureCamera * m_textureCamera;
	GLuint m_textureCameraUniform;



};

