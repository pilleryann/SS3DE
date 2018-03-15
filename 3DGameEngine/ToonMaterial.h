#pragma once
#ifndef TOON_MATERIAL
#define TOON_MATERIAL
#include "Material.h"
class ToonMaterial :
	public Material
{
public:
	ToonMaterial(GameObject * gameObject);
	~ToonMaterial();


	void SetMaterialToRender()override;
protected :
	void InitMaterialIntern() override;
};

#endif