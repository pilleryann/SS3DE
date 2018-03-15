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
	//Creer un vertexbuffer et lui assigne un ID 
	glGenBuffers(1, &vertexArrayID);
	// Dit de suivre ce vertexbuffer 
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayID);
	//Donne l'array de vertex à OpenGL
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

	//Creer un vertexbuffer et lui assigne un ID 
	glGenBuffers(1, &uvArrayID);
	// Dit de suivre ce vertexbuffer 
	glBindBuffer(GL_ARRAY_BUFFER, uvArrayID);
	//Donne l'array de vertex à OpenGL
	glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), &m_uvs[0], GL_STATIC_DRAW);

	//Creer un vertexbuffer et lui assigne un ID 
	glGenBuffers(1, &normalsArrayID);
	// Dit de suivre ce vertexbuffer 
	glBindBuffer(GL_ARRAY_BUFFER, normalsArrayID);
	//Donne l'array de vertex à OpenGL
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);
	
	
	//TODO make vertex colors

}

void Mesh::UnloadDataToGPU()
{
	glDeleteBuffers(1, &vertexArrayID);
	glDeleteBuffers(1, &uvArrayID);
	glDeleteBuffers(1, &normalsArrayID);
	//glDeleteBuffers(1, &vertexColorArrayID);
//	glDeleteVertexArrays(1, &vertexArrayID);
}
