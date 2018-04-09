#include "Mesh.h"

#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "Utils\SimpleObjLoader.h"
#include "GraphicsUtils.h"

#include <assimp\Importer.hpp>
#include <assimp\types.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


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

GLuint Mesh::GetTangentsArrayID()
{
	return tangentsArrayID;
}

GLuint Mesh::GetBitangentsArrayID()
{
	return bitangentsArrayID;
}

GLuint Mesh::GetIndicesArrayID()
{
	return indicesArrayID;
}

int Mesh::GetVertexArraySize()
{
	return m_vertices.size();
}

bool Mesh::LoadObjFromFile(std::string path)
{
	Assimp::Importer importer;
	
	//const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	LoadVertexArray(scene);
	LoadNormalsArray(scene);
	LoadUVArray(scene);
	LoadTangentsArray(scene);
	LoadBitangentsArray(scene);
	//LoadIndicesArray(scene);
	
	

	



	return true;
	//return SimpleObjLoader::loadOBJ(path.c_str(),m_vertices,m_uvs,m_normals);
}

void Mesh::LoadVertexArray(const aiScene * scene)
{
	aiVector3D* verticesSceneArray = scene->mMeshes[0]->mVertices;
	int numberOfVerticesInScene = scene->mMeshes[0]->mNumVertices;
	for (int i = 0; i < numberOfVerticesInScene; i++) {
		glm::vec3 vectice;
		aiVector3D aiVec = verticesSceneArray[i];
		vectice.x = aiVec.x;
		vectice.y = aiVec.y;
		vectice.z = aiVec.z;
		m_vertices.push_back(vectice);
	}
}

void Mesh::LoadUVArray(const aiScene * scene)
{
	//Get UVs 
	aiVector3D* uvSceneArray = scene->mMeshes[0]->mTextureCoords[0];
	int numberOfUVsInScene = scene->mMeshes[0]->mNumVertices;
	for (int i = 0; i < numberOfUVsInScene; i++) {
		glm::vec2 uv;
		aiVector3D aiVec = uvSceneArray[i];
		uv.x = aiVec.x;
		uv.y = aiVec.y;
		m_uvs.push_back(uv);
	}
}

void Mesh::LoadNormalsArray(const aiScene * scene)
{
	aiVector3D* normalSceneArray = scene->mMeshes[0]->mNormals;
	int numberOfNormalsInScene = scene->mMeshes[0]->mNumVertices;
	for (int i = 0; i < numberOfNormalsInScene; i++) {
		glm::vec3 normal;
		aiVector3D aiVec = normalSceneArray[i];
		normal.x = aiVec.x;
		normal.y = aiVec.y;
		normal.z = aiVec.z;
		m_normals.push_back(normal);
	}
}

void Mesh::LoadIndicesArray(const aiScene * scene)
{
	aiFace* facesSceneArray = scene->mMeshes[0]->mFaces;
	int numberOfFacesInScene = scene->mMeshes[0]->mNumFaces;
	for (int i = 0; i < numberOfFacesInScene; i++) {
		glm::vec3 vectice;
		aiFace face = facesSceneArray[i];
		unsigned int nbrIndicePeerFace = face.mNumIndices;
		for (unsigned int j = 0; j < nbrIndicePeerFace; j++) {
			m_indices.push_back(face.mIndices[j]);
		}	
	}
}

void Mesh::LoadTangentsArray(const aiScene * scene)
{
	aiVector3D* tangentsSceneArray = scene->mMeshes[0]->mTangents;
	int numberOfVerticesInScene = scene->mMeshes[0]->mNumVertices;
	for (int i = 0; i < numberOfVerticesInScene; i++) {
		glm::vec3 tangent;
		aiVector3D aiVec = tangentsSceneArray[i];
		tangent.x = aiVec.x;
		tangent.y = aiVec.y;
		tangent.z = aiVec.z;
		m_tangents.push_back(tangent);
	}
}

void Mesh::LoadBitangentsArray(const aiScene * scene)
{
	aiVector3D* tangentsSceneArray = scene->mMeshes[0]->mBitangents;
	int numberOfVerticesInScene = scene->mMeshes[0]->mNumVertices;
	for (int i = 0; i < numberOfVerticesInScene; i++) {
		glm::vec3 bitangent;
		aiVector3D aiVec = tangentsSceneArray[i];
		bitangent.x = aiVec.x;
		bitangent.y = aiVec.y;
		bitangent.z = aiVec.z;
		m_bitangents.push_back(bitangent);
	}
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

	//Génère les tangentes et bittangentes
	//GraphicsUtils::computeTangentBasis(m_vertices, m_uvs, m_normals, m_tangents, m_bitangents);
	//Assigner et loader les tangentes et bitangentes dans le GPU
	glGenBuffers(1, &tangentsArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, tangentsArrayID);
	glBufferData(GL_ARRAY_BUFFER, m_tangents.size() * sizeof(glm::vec3), &m_tangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &bitangentsArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentsArrayID);
	glBufferData(GL_ARRAY_BUFFER, m_bitangents.size() * sizeof(glm::vec3), &m_bitangents[0], GL_STATIC_DRAW);

	
	
	//TODO make vertex colors

}

void Mesh::UnloadDataToGPU()
{
	glDeleteBuffers(1, &vertexArrayID);
	glDeleteBuffers(1, &uvArrayID);
	glDeleteBuffers(1, &normalsArrayID);
	glDeleteBuffers(1, &tangentsArrayID);
	glDeleteBuffers(1, &bitangentsArrayID);

	//glDeleteBuffers(1, &vertexColorArrayID);
//	glDeleteVertexArrays(1, &vertexArrayID);
}
