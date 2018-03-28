#pragma once
#ifndef CAMERA
#define CAMERA
#include "Component.h"
#include "GameObject.h"
#include "glm\glm.hpp"
class Camera :
	public Component
{
public:
	Camera(GameObject * gameObject,glm::vec2 screenSize, float minClippingPane = 0.1f, float maxClippingPane = 1000.0f, float fieldOfView = 90.0f);
	~Camera();

	 void Start() override;
	 void Update() override;

	void LookAt(glm::vec3 targetPosition, glm::vec3 axisRotation);
	void SetScreenSize(float width, float height);
	void SetMinClippingPane(float minValue);
	void SetMaxClippingPane(float maxValue);
	void SetFieldOfView(float angle);

	void DefineAsMainCamera();

	glm::mat4 GetTransformViewProjection();
	glm::mat4 GetView();


private :
	glm::mat4 m_viewMatrix;
	glm::vec2 m_screenSize;
	float m_minClippingPane;
	float m_maxClippingPane;
	float m_fieldOfView;

};

#endif