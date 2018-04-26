#include "CameraControl.h"
#include "Camera.h"
#include "GameObject.h"

#include "Transform3D.h"

#include <SFML\Window.hpp>

#include "glm\glm.hpp"




CameraControl::CameraControl(GameObject * gameObject):Component(gameObject)
{
	
}

CameraControl::~CameraControl()
{
}

void CameraControl::Start()
{
	m_camera = m_gameObject->GetComponent<Camera>();
	//m_gameObject->GetComponent<Camera>();
	//m_camera = new Camera(m_gameObject, glm::vec2(10, 10));

}

void CameraControl::Update()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{

		glm::vec3 position = m_gameObject->GetTransform()->GetPosition();
		position.x += 0.1f;
		m_gameObject->GetTransform()->SetPosition(position);
		glm::vec3 directionToLook = m_gameObject->GetTransform()->GetPosition() + glm::vec3(0, 0, -1);
		m_camera->LookAt(directionToLook, glm::vec3(0, 1, 0));

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{

		glm::vec3 position = m_gameObject->GetTransform()->GetPosition();
		position.x -= 0.1f;
		m_gameObject->GetTransform()->SetPosition(position);
		glm::vec3 directionToLook = m_gameObject->GetTransform()->GetPosition() + glm::vec3(0, 0, -1);
		m_camera->LookAt(directionToLook, glm::vec3(0, 1, 0));

	}
}
