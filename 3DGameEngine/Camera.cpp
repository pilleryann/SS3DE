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
	glm::vec3 direction = targetPosition - transformPosition;
	glm::normalize(direction);

	glm::mat4 matLookAt = glm::lookAt(glm::vec3(0,0,0), direction, axisRotation);

	

	//matLookAt = matLookAt * glm::mat4(1.0f);


	//glm::vec4 directionLook = matLookAt * glm::vec4(0, 0, 1,0);
	glm::quat orientation = glm::toQuat(matLookAt);
	//orientation = glm::conjugate(orientation);
	glm::vec3 newRotation = glm::eulerAngles(orientation);
	newRotation = glm::degrees(newRotation);
	/*newRotation.x = 0;
	newRotation.z = 0;*/
	newRotation = -newRotation;
	printf("Orientation  : (%f,%f,%f,%f)\n", orientation.x, orientation.y, orientation.z, orientation.w);
	printf("NewRotation  : (%f,%f,%f)\n", newRotation.x, newRotation.y, newRotation.z);
	/*glm::decompose(matLookAt, scale, orientation, translation, skew, perspective);
	//TODO à verifier
	orientation = glm::conjugate(orientation);//PArait que ça le met comme il faut 
	glm::vec3 newRotation = glm::eulerAngles(orientation);
	printf("Orientation  : (%f,%f,%f,%f)\n", orientation.x, orientation.y, orientation.z,orientation.w);
	printf("NewRotation  : (%f,%f,%f)\n", newRotation.x, newRotation.y, newRotation.z);
	newRotation = glm::degrees(newRotation);*/

	m_gameObject->GetTransform()->SetRotation(newRotation);
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

glm::mat4 Camera::GetTransformView()
{
	glm::mat4 Projection = glm::perspective(glm::radians(m_fieldOfView), (float)m_screenSize.x / (float)m_screenSize.y, m_minClippingPane, m_maxClippingPane);
	//glm::mat4 View = glm::lookAt(cameraPosition, lookAtPosition, glm::vec3(0, 1, 0));

	//Get informations from the transform
	glm::vec3  transformRotation = m_gameObject->GetTransform()->GeRotation();
	glm::vec3  transformPosition = m_gameObject->GetTransform()->GetPosition();
	glm::mat4 rotation = glm::eulerAngleXYZ(glm::radians(transformRotation.x), glm::radians(transformRotation.y), glm::radians(transformRotation.z));
	glm::mat4 translate = glm::translate(transformPosition);


	glm::mat4 View = rotation * translate ;
	glm::mat4 Model = glm::mat4(0.1f);

	//S'applique dans l'orde Model puis View puis Projection
	glm::mat4 mvp = Projection * View * Model;


	return mvp;//Retourne une copie de la matrice 
}


