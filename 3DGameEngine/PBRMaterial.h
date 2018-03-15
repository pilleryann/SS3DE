#pragma once
#ifndef PBR_MATERIAL
#define PBR_MATERIAL
#include "Material.h"
class PBRMaterial :
	public Material
{
public:
	PBRMaterial(GameObject * gameObject);
	~PBRMaterial();


	void SetMaterialToRender()override;

protected :
	void InitMaterialIntern() override;

};

#endif