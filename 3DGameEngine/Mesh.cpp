#include "Mesh.h"

#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "Utils\SimpleObjLoader.h"

Mesh::Mesh(std::string path)
{
	LoadObjFromFile(path);
	
}


Mesh::~Mesh()
{
	UnloadDataToGPU();
}

void Mesh::Init()
{
	LoadDataToGPU();
}

GLuint Mesh::GetVertexArrayID()
{
	return vertexArrayID;
}

GLuint Mesh::GetVertexColorArrayID()
{
	return vertexColorArrayID;
}

GLuint Mesh::GetNormalsArrayID()
{
	return normalsArrayID;
}

GLuint Mesh::GetUVArrayID()
{
	return uvArrayID;
}

int Mesh::GetVertexArraySize()
{
	return m_vertices.size();
}

bool Mesh::LoadObjFromFile(std::string path)
{
	return SimpleObjLoader::loadOBJ(path.c_str(),m_vertices,m_uvs,m_normals);
}

void Mesh::LoadDataToGPU()
{

	//Définir, récupérer l'ID du vertex buffer 
	//Envoyer les data dans le vertex buffer 
	
	//TODO a remplir

	//Définir, récupérer l'ID de l'UV buffer 
	//Envoyer les data dans l'UV buffer buffer 

	//TODO a remplir


	//Définir, récupérer l'ID du normals buffer 
	//Envoyer les data dans le normals buffer 

	//TODO a remplir

	//Définir, récupérer l'ID du color vertex buffer 
	//Envoyer les data dans le color vertex buffer 

	//TODO a remplir
	

}

void Mesh::UnloadDataToGPU()
{
	glDeleteBuffers(1, &vertexArrayID);
	glDeleteBuffers(1, &uvArrayID);
	glDeleteBuffers(1, &normalsArrayID);
	glDeleteBuffers(1, &vertexColorArrayID);

}
