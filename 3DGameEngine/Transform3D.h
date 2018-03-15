#pragma once
#ifndef TRANSFORM_3D
#define TRANSFORM_3D
#include "Component.h"
#include "glm/glm.hpp"
class Transform3D :
	public Component
{
public:

	Transform3D(GameObject * gameObject,glm::vec3 position=glm::vec3(0,0,0), glm::vec3 rotation = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1));
	
	~Transform3D();

	 void Start() override;
	 void Update() override;

	 glm::vec3 GetPosition();
	 glm::vec3 GeRotation();
	 glm::vec3 GetScale();

	 void SetPosition(glm::vec3 position);
	 void SetRotation(glm::vec3 rotation);
	 void SetScale(glm::vec3 scale);

	 glm::mat4 GetMatrixTransformation();


private :
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;


};
#endif
