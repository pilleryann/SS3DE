#pragma once
#include "Material.h"
#include "glm\glm.hpp"

class LightComponent;

class VisualLightMaterial :
	public Material
{
public:
	VisualLightMaterial(GameObject * gameObject, LightComponent * light );
	~VisualLightMaterial();

	void SetMaterialToRender() override;

private :
	LightComponent * m_lightComponent;
	GLuint m_lightColorUniformID; 


protected:
	void InitMaterialIntern() override;
};

