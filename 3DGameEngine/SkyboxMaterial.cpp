#include "SkyboxMaterial.h"
#include "CubeMapTexture.h"




SkyboxMaterial::SkyboxMaterial(GameObject * gameObject, CubeMapTexture * skyboxTexture):Material(gameObject,"Shaders/SkyboxShader.vertex","Shaders/SkyboxShader.fragment")
{
	m_skyboxTexture = skyboxTexture;
}

SkyboxMaterial::~SkyboxMaterial()
{
	delete m_skyboxTexture;
}

void SkyboxMaterial::SetMaterialToRender()
{
	glUseProgram(shaderID);

	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxTexture->GetTexureID());
	glUniform1i(m_textureID,/*GL_TEXTURE_2D*/0);//Le bind ici doit se faire avec l'unité de texture

}

void SkyboxMaterial::InitMaterialIntern()
{

	glGetUniformLocation(shaderID, "skybox");
}
