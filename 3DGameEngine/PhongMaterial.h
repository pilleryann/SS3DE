#pragma once
#ifndef PHONG_MATERIAL
#define PHONG_MATERIAL
#include "Material.h"
class PhongMaterial :
	public Material
{
public:
	PhongMaterial(GameObject * gameObject);
	~PhongMaterial();

	void SetMaterialToRender()override;

protected : 
	void InitMaterialIntern() override;
};

#endif