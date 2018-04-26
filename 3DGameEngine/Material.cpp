#include "Material.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>


#include <stdlib.h>
#include <string.h>


#include <GL/glew.h>

#include "LightComponent.h"
#include "GameObject.h"
#include "Engine.h"
#include "Camera.h"
#include "Transform3D.h"







Material::Material(GameObject * gameObject,std::string vertexShaderPath,std::string fragmentShaderPath)
{
	LoadShader(vertexShaderPath, fragmentShaderPath);
	m_gameObject = gameObject;

	std::vector<LightComponent*> * lightsList = m_gameObject->GetEngine()->getLightsInScene();
	if (lightsList->size() != 0)
	{
		LightComponent* light = lightsList->at(0);
		lightPosition = light->getPosition();
		lightPower = light->getLightPower();
		lightColor = light->getLightColor();
	}


}

Material::~Material()
{
}

void Material::InitMaterial()
{
	glUseProgram(shaderID);
	printf("Init Material basis \n");

	//Init View part 
	//Recupere le handler pour le MVP uniform qui se retrouve dans le shader.
	//Grace a ça, nous pouvons mettre à jour la position de la caméra.
	matrixMVP_ID = glGetUniformLocation(shaderID, "MVP");

	//Récupérer les autres Handlers des shaders 

	matrixM_ID = glGetUniformLocation(shaderID, "M");
	matrixV_ID = glGetUniformLocation(shaderID, "V");
	matrixP_ID = glGetUniformLocation(shaderID, "P");

	matrixMV3x3_ID = glGetUniformLocation(shaderID, "matrixMV3x3");

	viewForKybox_ID = glGetUniformLocation(shaderID, "skyboxView");

	lightWorldPosition_ID = glGetUniformLocation(shaderID, "LightPosition_worldspace");
	lightColor_ID = glGetUniformLocation(shaderID, "lightColor");
	lightPower_ID = glGetUniformLocation(shaderID, "LightPower");


	InitMaterialIntern();
 
}

void Material::UpdateCameraTransform()
{ 

	
	//glm::mat4 mvp = CalculateModelViewProjection(45, 800, 600, 0.1f, 1000, cameraPosition, cameraTarget);
	glm::mat4 projectionMatrix = m_gameObject->GetEngine()->GetMainCamera()->GetTransformViewProjection();
	glm::mat4 viewMatrix = m_gameObject->GetEngine()->GetMainCamera()->GetView();
	glm::mat4 modelMatrix = m_gameObject->GetTransform()->GetMatrixTransformation();
	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
	//glm::mat4 modelMatrix = CalculateModelMatrix(glm::vec4(0, 1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 skyboxView = glm::mat4(glm::mat3(viewMatrix));
	//mvp = mvp * modelMatrix;

	glm::mat3 modelView3x3 = glm::mat3(modelViewMatrix);
	//glm::mat3 modelView3x3 = glm::mat3(modelMatrix);

	//Envoie la matrice mvp dans le shader. Dans ce cas, c'est pour appliquer une projetion et déplacement de la caméra.

	glUniformMatrix4fv(matrixMVP_ID, 1, GL_FALSE, &mvp[0][0]);

	//Envoie divers informations pour les lumières dans le shader 
	glUniformMatrix4fv(matrixM_ID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(matrixV_ID, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(matrixP_ID, 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniformMatrix3fv(matrixMV3x3_ID, 1, GL_FALSE, &modelView3x3[0][0]);
	glUniformMatrix4fv(viewForKybox_ID, 1, GL_FALSE, &skyboxView[0][0]);
	glUniform3fv(lightWorldPosition_ID, 1, &lightPosition[0]);
	glUniform3fv(lightColor_ID, 1, &lightColor[0]);
	glUniform1f(lightPower_ID, lightPower);
	
}

void Material::LoadShader(std::string vertex_file_path, std::string fragment_file_path)
{

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path.c_str());
		getchar();
		
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}



	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	shaderID =  ProgramID;
}

glm::mat4 Material::CalculateModelViewProjection(float fieldOfView, int width, int height, float minRange, float maxRange, glm::vec3 cameraPosition, glm::vec3 lookAtPosition)
{


	glm::mat4 Projection = glm::perspective(glm::radians(fieldOfView), (float)width / (float)height, minRange, maxRange);
	glm::mat4 View = glm::lookAt(cameraPosition, lookAtPosition, glm::vec3(0, 1, 0));
	glm::mat4 Model = glm::mat4(0.1f);

	//S'applique dans l'orde Model puis View puis Projection
	glm::mat4 mvp = Projection * View * Model;


	return mvp;//Retourne une copie de la matrice 
}

glm::mat4 Material::CalculateModelMatrix(glm::vec4 rotationQuaternion, glm::vec3 translation, glm::vec3 scale)
{
	glm::mat4 TranslationMat4 = glm::translate(glm::mat4(), translation);
	glm::mat4 ScaleMat4 = glm::scale(scale);
	glm::vec3 rotationAxis = glm::vec3(rotationQuaternion.x, rotationQuaternion.y, rotationQuaternion.z);
	glm::mat4 RotationMat4 = glm::rotate(rotationQuaternion.w, rotationAxis);

	glm::mat4 modelMatrix = TranslationMat4 * RotationMat4 * ScaleMat4;

	return modelMatrix;
}

