#pragma once
#include "Component.h"
#include "glm\glm.hpp"

class LightComponent :
	public Component
{
public:
	LightComponent(GameObject * gameObject,glm::vec3 position,float lightPower,glm::vec3 lightColor);
	~LightComponent();


	 void Start() ;
	 void Update() ;

	 glm::vec3 getLightColor();
	 float getLightPower();
	 glm::vec3 getPosition();
	 

private: 

	glm::vec3 m_lightColor;
	float m_lightPower;

};

