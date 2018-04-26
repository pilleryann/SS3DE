#include "Camera.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "glm\gtx\matrix_decompose.hpp"
#include "GameObject.h"
#include "Transform3D.h"

Camera::Camera(GameObject * gameObject,glm::vec2 screenSize,float minClippingPane,float maxClippingPane,float fieldOfView):Component(gameObject)
{
	m_screenSize = screenSize;
	m_minClippingPane = minClippingPane;
	m_maxClippingPane = maxClippingPane;
	m_fieldOfView = fieldOfView;
	m_viewMatrix = glm::scale(glm::vec3(1, 1, 1));
	DefineAsMainCamera();
}


Camera::~Camera()
{
}

void Camera::Start()
{
	
}

void Camera::Update()
{
}

void Camera::LookAt(glm::vec3 targetPosition,glm::vec3 axisRotation)
{
	


	glm::vec3  transformPosition = m_gameObject->GetTransform()->GetPosition();
//	glm::vec3 direction = targetPosition - transformPosition;
	//glm::normalize(direction);

	m_viewMatrix = glm::lookAt(transformPosition, targetPosition, axisRotation);

	

	/*
	
	glm::quat orientation = glm::toQuat(matLookAt);
	orientation = glm::conjugate(orientation);
	glm::vec3 newRotation = glm::eulerAngles(orientation);
	newRotation = glm::degrees(newRotation);

	printf("Orientation  : (%f,%f,%f,%f)\n", orientation.x, orientation.y, orientation.z, orientation.w);
	printf("NewRotation  : (%f,%f,%f)\n", newRotation.x, newRotation.y, newRotation.z);


	m_gameObject->GetTransform()->SetRotation(newRotation);
	*/
}

void Camera::SetScreenSize(float width, float height)
{
	m_screenSize.x = width;
	m_screenSize.y = height;
}

void Camera::SetMinClippingPane(float minValue)
{
	m_minClippingPane = minValue;
}

void Camera::SetMaxClippingPane(float maxValue)
{
	m_maxClippingPane = maxValue;
}

void Camera::SetFieldOfView(float angle)
{
	m_fieldOfView = angle;
}

void Camera::DefineAsMainCamera()
{
	m_gameObject->GetEngine()->SetMainCamera(this);
}

glm::mat4 Camera::GetTransformViewProjection()
{
	glm::mat4 Projection = glm::perspective(glm::radians(m_fieldOfView), (float)m_screenSize.x / (float)m_screenSize.y, m_minClippingPane, m_maxClippingPane);
	


	//Get informations from the transform
/*	glm::vec3  transformRotation = - (m_gameObject->GetTransform()->GeRotation());
	glm::vec3  transformPosition = m_gameObject->GetTransform()->GetPosition();
	glm::mat4 rotation = glm::eulerAngleXYZ(glm::radians(transformRotation.x), glm::radians(transformRotation.y), glm::radians(transformRotation.z));
	glm::mat4 translate = glm::translate(transformPosition);


	glm::mat4 View = rotation * translate ;*/
//	glm::mat4 Model = glm::mat4(1.0f);

	//S'applique dans l'orde Model puis View puis Projection
	//glm::mat4 mvp = Projection * m_viewMatrix * Model;


	return Projection;//Retourne une copie de la matrice 
}

glm::mat4 Camera::GetView()
{
	return m_viewMatrix;
}


