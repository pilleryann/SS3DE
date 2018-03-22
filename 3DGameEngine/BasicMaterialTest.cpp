#include "BasicMaterialTest.h"
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "GameObject.h"
#include "Transform3D.h" 
#include "Camera.h"
#include "Engine.h"

BasicMaterialTest::BasicMaterialTest(GameObject * gameObject):Material(gameObject,"Shaders/BasicShaderTest.vertex","Shaders/BasicShaderTest.fragment")
{
	printf("Basic Material constructor. \n");

	 lightPosition = glm::vec3(4, 3, 3);
	 lightPower = 40.0f;
	 lightColor = glm::vec3(1, 1, 1);

	
}

BasicMaterialTest::~BasicMaterialTest()
{
	printf("Basic material destructor \n");
	glDeleteProgram(shaderID);
	delete m_texture;
}





void BasicMaterialTest::SetMaterialToRender()
{
	glUseProgram(shaderID);//Bind shader

							//Créer la position de la lumière





	//Applique le model matrix, le view matrix et enifin la projetction matrix. Le tout dans l'ordre. 
	//Atttention : Avec les multiplication cela inverse l'ordre des application  :
	// projectionMatix*viewMatrix*modelMatrix
	glm::vec3 cameraPosition = glm::vec3(4, 2, 3);
	glm::vec3 cameraTarget = glm::vec3(0, 0, 0);

	//glm::mat4 mvp = CalculateModelViewProjection(45, 800, 600, 0.1f, 1000, cameraPosition, cameraTarget);
	glm::mat4 mvp = m_gameObject->GetEngine()->GetMainCamera()->GetTransformView();
	//glm::mat4 modelMatrix = CalculateModelMatrix(glm::vec4(0, 1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 modelMatrix = m_gameObject->GetTransform()->GetMatrixTransformation();
	mvp = mvp * modelMatrix;
	glm::mat4 viewMatrix = glm::lookAt(cameraPosition, cameraTarget, glm::vec3(0, 1, 0));
	glm::mat3 modelView3x3 = glm::mat3(viewMatrix*modelMatrix);

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

	m_texture = new TextureEngine3D("Datas/singe.DDS");

	TextureID = glGetUniformLocation(shaderID, "myTextureSampler");
	glUniform1i(TextureID, m_texture->GetTexureID());


	//Normals map 

	m_normalsMap = new TextureEngine3D("Datas/normals.DDS");

	normalMapID = glGetUniformLocation(shaderID, "NormalTextureSampler");
	glUniform1i(normalMapID, m_normalsMap->GetTexureID());


	lightWorldPosition_ID = glGetUniformLocation(shaderID, "LightPosition_worldspace");
	lightColor_ID = glGetUniformLocation(shaderID, "lightColor");
	lightPower_ID = glGetUniformLocation(shaderID, "LightPower");

	
}
