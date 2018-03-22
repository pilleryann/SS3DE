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
	//printf("Render 3D Update \n");
	// Calcul le shader : Postion camera, lumières, position objet et lumière
	m_material->SetMaterialToRender();
	
	//Draw triangle  


	//--------- Ajouter l'attribut des position sur les vertex-----------


	//fprintf(stdout, "Draw!\n");
	//On applique l'ID d'attribut de vertex à 0. Dans le shader on peur le récupérer avec "location".
	glEnableVertexAttribArray(0);//Ouverture edtion buffer sur l'attribut ID = 0. On décide que cela correspond au couleur des vertex.
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->GetVertexArrayID());//Choix du buffer
	glVertexAttribPointer(
		0, // Attribuer un layer ==> pour shader. 0 est un choix arbitraire
		3, // size
		GL_FLOAT, //type
		GL_FALSE, // normalized 
		0, // stride
		(void*)0 //Array buffer offset
	);


	//--------- Ajouter l'attribut des couleurs sur les vertex-----------


	glEnableVertexAttribArray(1);//Ouverture edtion buffer sur l'attribut ID = 0. On décide que cela correspond au couleur des vertex.
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->GetNormalsArrayID());//Choix du buffer
	glVertexAttribPointer(
		1, // Attribuer un layer ==> pour shader. 0 est un choix arbitraire
		3, // size
		GL_FLOAT, //type
		GL_FALSE, // normalized 
		0, // stride
		(void*)0 //Array buffer offset
	);


	// Ajouter l'attribut UV
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->GetUVArrayID());
	glVertexAttribPointer(
		2,
		2,//Size ==> coordonnees 2 dimensions pour les UV 
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// Ajouter l'attribut tangents
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->GetTangentsArrayID());
	glVertexAttribPointer(
		4,
		3,//Size ==> coordonnees 3 dimensions pour les tangents 
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);


	// Ajouter l'attribut bitangents
	glEnableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->GetBitangentsArrayID());
	glVertexAttribPointer(
		5,
		3,//Size ==> coordonnees 3 dimensions pour les bitangents 
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);


	// Ajouter l'attribut vertex color
/*	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, m_mesh->GetVertexColorArrayID());
	glVertexAttribPointer(
		3,
		3,//Size ==> coordonnees 3 dimensions pour les couleurs 
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	*/

	//On a 12 triangle et on doit mettre le nombre de vectices à dessiner
	glDrawArrays(GL_TRIANGLES, 0,m_mesh->GetVertexArraySize());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);

	//Remarque : Chaques sommets est écrit 2 fois, cela peut prendre de la place.

}
