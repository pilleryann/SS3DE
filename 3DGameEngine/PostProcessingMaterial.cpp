#include "PostProcessingMaterial.h"



PostProcessingMaterial::PostProcessingMaterial(GameObject * gameObject,TextureCamera * textureCamera) :
	Material( gameObject,"Shaders/PostProcessingShader.vertex", "Shaders/PostProcessingShader.fragment")
{
	m_textureCamera = textureCamera;
}


PostProcessingMaterial::~PostProcessingMaterial()
{
}

void PostProcessingMaterial::SetMaterialToRender()
{
	glUseProgram(shaderID);
	//glUseProgram(shaderID);//Bind shader

	//Créer la position de la lumière
	//glActiveTexture(GL_TEXTURE0);	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureCamera->GetTexureID());
	glUniform1i(m_textureCameraUniform,/*GL_TEXTURE_2D*/0);//Le bind ici doit se faire avec l'unité de texture

	glBindTexture(GL_TEXTURE_2D,0);

}

void PostProcessingMaterial::InitMaterialIntern()
{
	glUseProgram(shaderID);

	m_textureCameraUniform =  glGetUniformLocation(shaderID, "screenTexture");
	
}
