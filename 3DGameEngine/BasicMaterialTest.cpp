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





	//Calculer la caméra en utilisant les information provenant de la main camera et de son transform

	//TODO
	
	//Envnoyer les paramètres au shader 

	//TODO
}

void BasicMaterialTest::InitMaterialIntern()
{
	printf("Basic material initialisation Intern \n");

	m_texture = new TextureEngine3D("Datas/singe.DDS");

	TextureID = glGetUniformLocation(shaderID, "myTextureSampler");
	glUniform1i(TextureID, m_texture->GetTexureID());


	lightWorldPosition_ID = glGetUniformLocation(shaderID, "LightPosition_worldspace");
	lightColor_ID = glGetUniformLocation(shaderID, "lightColor");
	lightPower_ID = glGetUniformLocation(shaderID, "LightPower");

	
}
