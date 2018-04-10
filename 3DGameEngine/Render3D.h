#pragma once
#ifndef RENDER_3D
#define RENDER_3D


#include "Component.h"
#include "Material.h"
#include "Mesh.h"
//#include <gl\GLU.h>

class Render3D :
	public Component
{
public:
	Render3D(GameObject * gameObject, std::string path);
	Render3D(GameObject * gameObject,Mesh * mesh, Material * material);
	~Render3D();


	 void Start() override;
	 void Update() override;

	 

private:
	Material * m_material;
	Mesh * m_mesh;

//	GLuint cas
};

#endif // !RENDER_3D