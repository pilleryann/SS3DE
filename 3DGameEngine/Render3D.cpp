#include "Render3D.h"
#include "glm\glm.hpp"
#include "glm\matrix.hpp"
#include "glm\ext.hpp"
#include <gl\glew.h>
#include "BasicMaterialTest.h"



Render3D::Render3D(GameObject * gameObject):Component(gameObject)
{
	printf("Constructor Render3D\n");

	m_mesh = new Mesh("Datas/singe.obj");
	BasicMaterialTest * basicMaterial = new BasicMaterialTest(m_gameObject);
	m_material = basicMaterial;
}

Render3D::Render3D(GameObject * gameObject, Mesh * mesh, Material *material): Component(gameObject)
{
	m_mesh = mesh;
	m_material = material;
	
}

Render3D::~Render3D()
{
	printf("Render 3D destruction \n");
	delete m_mesh;
	delete m_material;
}

void Render3D::Start()
{
	printf("Render 3D Start : init material \n");
	m_mesh->Init();
	m_material->InitMaterial();
}

void Render3D::Update()
{

	// Calcul le shader : Postion camera, lumières, position objet et lumière
	m_material->SetMaterialToRender();
	



	//--------- Ajouter l'attribut des position sur les vertex-----------


	//TODO à remplir


	//--------- Ajouter l'attribut des normals sur les vertex-----------


	//TODO a remplir 


	// Ajouter l'attribut UV par vertex
		
	
	//TODO a remplir 

	// Ajouter l'attribut vertex color


	//Dessiner les triangles
	glDrawArrays(GL_TRIANGLES, 0,m_mesh->GetVertexArraySize());

	//Ferme les attributs 
	//TODO à remplir

	//Remarque : Chaques sommets est écrit 2 fois, cela peut prendre de la place.

}
