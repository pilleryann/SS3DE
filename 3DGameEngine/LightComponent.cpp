#include "LightComponent.h"
#include "GameObject.h"
#include "Transform3D.h"
#include "Mesh.h"
#include "VisualLightMaterial.h"
#include "Render3D.h"



LightComponent::LightComponent(GameObject * gameObject, glm::vec3 position, float lightPower, glm::vec3 lightColor):Component(gameObject)
{
	m_gameObject->GetTransform()->SetPosition(position);
	m_lightPower = lightPower;
	m_lightColor = lightColor;
	//Add automatically the light in scene
	gameObject->GetEngine()->getLightsInScene()->push_back(this);

	//Cr�er/loader un mesh de type lumi�re 
	Mesh * mesh = new Mesh("Datas/Sphere3.obj");

	//Cr�er un nouveau mat�rial pour les lumi�re 
	VisualLightMaterial * mat = new VisualLightMaterial(m_gameObject, this);

	//Cr�er un render 3D  assignre le mesh et le material 
	Render3D *  render = new Render3D(m_gameObject, mesh, mat);

	//Ajouter le render 3d dans le GameObject
	m_gameObject->AddComponent(render);

}

LightComponent::~LightComponent()
{
	std::vector<LightComponent*> * lightsList  = m_gameObject->GetEngine()->getLightsInScene();	
	lightsList->erase(std::remove(lightsList->begin(), lightsList->end(), this), lightsList->end());
}

void LightComponent::Start()
{
}

void LightComponent::Update()
{
}

glm::vec3 LightComponent::getLightColor()
{
	return m_lightColor;
}

float LightComponent::getLightPower()
{
	return m_lightPower;
}

glm::vec3 LightComponent::getPosition()
{
	return m_gameObject->GetTransform()->GetPosition();
}
