#pragma once
#ifndef MESH
#define MESH
#include <GL\glew.h>
#include <string>
#include <vector>
#include "glm\glm.hpp"
/*
	Permet de loader le mesh depuis un fichier obj et charge dans la carte graphique les datas.
*/
class Mesh
{
public:

	Mesh(std::string path);
	~Mesh();

	void Init();

	GLuint GetVertexArrayID();
	GLuint GetVertexColorArrayID();
	GLuint GetNormalsArrayID();
	GLuint GetUVArrayID();
	GLuint GetTangentsArrayID();
	GLuint GetBitangentsArrayID();

	int GetVertexArraySize();





private :
	std::string m_path;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_tangents;
	std::vector<glm::vec3> m_bitangents;


	GLuint vertexArrayID;
	GLuint vertexColorArrayID;
	GLuint normalsArrayID;
	GLuint uvArrayID;

	GLuint tangentsArrayID;
	GLuint bitangentsArrayID;




	bool LoadObjFromFile(std::string path);
	void LoadDataToGPU();
	void UnloadDataToGPU();
};

#endif