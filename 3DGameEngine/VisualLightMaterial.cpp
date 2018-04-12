#include "VisualLightMaterial.h"
#include "LightComponent.h"


VisualLightMaterial::VisualLightMaterial(GameObject * gameObject, LightComponent * light):Material(gameObject,"Shaders/BasicShaderTest.vertex","Shaders/VisualLight.fragment")
{
	m_lightComponent = light;
}

VisualLightMaterial::~VisualLightMaterial()
{

}

void VisualLightMaterial::SetMaterialToRender()
{

	glUseProgram(shaderID);//Bind shader

	glm::vec3 lightColor = m_lightComponent->getLightColor();
	glUniform3fv(m_lightColorUniformID,1,&lightColor[0]);
	UpdateCameraTransform();
}

void VisualLightMaterial::InitMaterialIntern()
{
	
	m_lightColorUniformID =  glGetUniformLocation(shaderID, "lightColor");
}
