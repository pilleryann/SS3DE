#include "BasicMaterialTest.h"
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "GameObject.h"
#include "Transform3D.h" 
#include "Camera.h"
#include "Engine.h"
#include "LightComponent.h"

BasicMaterialTest::BasicMaterialTest(GameObject * gameObject):Material(gameObject,"Shaders/BasicShaderTest.vertex","Shaders/BasicShaderTest.fragment")
{
	printf("Basic Material constructor. \n");

	std::vector<LightComponent*> * lightsList = m_gameObject->GetEngine()->getLightsInScene();

	LightComponent* light = lightsList->at(0);
	lightPosition = light->getPosition();
	lightPower = light->getLightPower();
	lightColor = light->getLightColor();

	/*
	 lightPosition = glm::vec3(2, 0,5);
	 lightPower = 10.0f;
	 lightColor = glm::vec3(1, 1, 1);

	 */

	
}

BasicMaterialTest::BasicMaterialTest(GameObject * gameObject, std::string albedoPath, std::string normalPath):BasicMaterialTest(gameObject)
{
	m_albedoPath = albedoPath;
	m_normalPath = normalPath;
}

BasicMaterialTest::~BasicMaterialTest()
{
	printf("Basic material destructor \n");
	glDeleteProgram(shaderID);
	delete m_texture;
	delete m_normalsMap;
}





void BasicMaterialTest::SetMaterialToRender()
{
	glUseProgram(shaderID);//Bind shader

							//Créer la position de la lumière





	//Applique le model matrix, le view matrix et enifin la projetction matrix. Le tout dans l'ordre. 
	//Atttention : Avec les multiplication cela inverse l'ordre des application  :
	// projectionMatix*viewMatrix*modelMatrix


	//glm::mat4 mvp = CalculateModelViewProjection(45, 800, 600, 0.1f, 1000, cameraPosition, cameraTarget);
	glm::mat4 projectionMatrix = m_gameObject->GetEngine()->GetMainCamera()->GetTransformViewProjection();
	glm::mat4 viewMatrix = m_gameObject->GetEngine()->GetMainCamera()->GetView();
	glm::mat4 modelMatrix = m_gameObject->GetTransform()->GetMatrixTransformation();
	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
	//glm::mat4 modelMatrix = CalculateModelMatrix(glm::vec4(0, 1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	
	//mvp = mvp * modelMatrix;
	
	glm::mat3 modelView3x3 = glm::mat3(modelViewMatrix);
	//glm::mat3 modelView3x3 = glm::mat3(modelMatrix);

	//Envoie la matrice mvp dans le shader. Dans ce cas, c'est pour appliquer une projetion et déplacement de la caméra.

	glUniformMatrix4fv(matrixMVP_ID, 1, GL_FALSE, &mvp[0][0]);

	//Envoie divers informations pour les lumières dans le shader 
	glUniformMatrix4fv(matrixM_ID, 1, GL_FALSE, &modelMatrix[0][0]);
	glUniformMatrix4fv(matrixV_ID, 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix3fv(matrixMV3x3_ID,1, GL_FALSE, &modelView3x3[0][0]);
	glUniform3fv(lightWorldPosition_ID, 1, &lightPosition[0]);
	glUniform3fv(lightColor_ID, 1, &lightColor[0]);
	glUniform1f(lightPower_ID, lightPower);
	//glUniform1fv(l)

	//glUniform3f()
}

void BasicMaterialTest::InitMaterialIntern()
{
	printf("Basic material initialisation Intern \n");

	m_texture = new TextureEngine3D(m_albedoPath);

	TextureID = glGetUniformLocation(shaderID, "myTextureSampler");
	
	glUniform1i(TextureID, m_texture->GetTexureID());

	//Normals map 

	m_normalsMap = new TextureEngine3D(m_normalPath);

	normalMapID = glGetUniformLocation(shaderID, "NormalTextureSampler");
	glUniform1i(normalMapID, m_normalsMap->GetTexureID());


	lightWorldPosition_ID = glGetUniformLocation(shaderID, "LightPosition_worldspace");
	lightColor_ID = glGetUniformLocation(shaderID, "lightColor");
	lightPower_ID = glGetUniformLocation(shaderID, "LightPower");

	
}
