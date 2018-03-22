#pragma once
#ifndef MATERIAL
#define MATERIAL
#include <string>
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"

class GameObject;

class Material
{
public:
	Material(GameObject * gameObject, std::string vertexShaderPath, std::string fragmentShaderPath);
	~Material();

	void InitMaterial();
	virtual void SetMaterialToRender() = 0;



protected :
	GameObject * m_gameObject;
	GLuint shaderID;
	
	//Camera part

	GLuint matrixMVP_ID;
	GLuint matrixM_ID;
	GLuint matrixV_ID;
	GLuint matrixMV3x3_ID;



	glm::mat4 CalculateModelViewProjection(float fieldOfView, int width, int height, float minRange, float maxRange, glm::vec3 cameraPosition, glm::vec3 lookAtPosition);
	glm::mat4 CalculateModelMatrix(glm::vec4 rotationQuaternion, glm::vec3 translation, glm::vec3 scale);
    void LoadShader(std::string vertex_file_path, std::string fragment_file_path);

	virtual void InitMaterialIntern() = 0;

};

#endif