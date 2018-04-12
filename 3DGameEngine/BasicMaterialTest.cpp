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

							//Cr�er la position de la lumi�re
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(TextureID, /*GL_TEXTURE*/0);
	glBindTexture(GL_TEXTURE_2D, m_texture->GetTexureID());
	
	glActiveTexture(GL_TEXTURE1);
	glUniform1i(normalMapID, /*GL_TEXTURE*/1);
	glBindTexture(GL_TEXTURE_2D, m_normalsMap->GetTexureID());
	//Applique le model matrix, le view matrix et enifin la projetction matrix. Le tout dans l'ordre. 
	//Atttention : Avec les multiplication cela inverse l'ordre des application  :
	// projectionMatix*viewMatrix*modelMatrix

	UpdateCameraTransform();

	//glUniform1fv(l)

	//glUniform3f()
}

void BasicMaterialTest::InitMaterialIntern()
{
	printf("Basic material initialisation Intern \n");

	m_texture = new TextureEngine3D(m_albedoPath);

	TextureID = glGetUniformLocation(shaderID, "myTextureSampler");
	


	//Normals map 

	m_normalsMap = new TextureEngine3D(m_normalPath);

	normalMapID = glGetUniformLocation(shaderID, "NormalTextureSampler");
	
	
	glUniform1i(TextureID, m_texture->GetTexureID());
	
	glUniform1i(normalMapID, m_normalsMap->GetTexureID());


	

	
}
