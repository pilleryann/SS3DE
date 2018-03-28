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
struct aiScene;
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
	GLuint GetIndicesArrayID();

	int GetVertexArraySize();





private :
	std::string m_path;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_uvs;
	std::vector<glm::vec3> m_normals;
	std::vector<glm::vec3> m_tangents;
	std::vector<glm::vec3> m_bitangents;
	std::vector<unsigned int> m_indices;


	//TODO A faire bientot 
	GLuint vertexArrayObjectID;

	GLuint vertexArrayID;
	GLuint vertexColorArrayID;
	GLuint normalsArrayID;
	GLuint uvArrayID;
	GLuint indicesArrayID;

	GLuint tangentsArrayID;
	GLuint bitangentsArrayID;




	bool LoadObjFromFile(std::string path);
	void LoadVertexArray(const aiScene* scene);
	void LoadUVArray(const aiScene* scene);
	void LoadNormalsArray(const aiScene* scene);
	void LoadIndicesArray(const aiScene* scene);
	void LoadTangentsArray(const aiScene* scene);
	void LoadBitangentsArray(const aiScene* scene);
	

	void LoadDataToGPU();
	void UnloadDataToGPU();
};

#endif