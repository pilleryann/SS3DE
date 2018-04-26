#include "ObjectMovement.h"
#include <SFML\Window.hpp>
#include "GameObject.h"
#include "Transform3D.h"
#include "glm\glm.hpp"




ObjectMovement::ObjectMovement(GameObject * gameObject, sf::Keyboard::Key keyLeft, 
	sf::Keyboard::Key keyRight, sf::Keyboard::Key keyForward, sf::Keyboard::Key keyBackward, 
	sf::Keyboard::Key keyRotationLeft, sf::Keyboard::Key keyRotationRight):Component(gameObject)
{
	 m_keyLeft= keyLeft;
	 m_keyRight= keyRight;
	 m_keyForward= keyForward;
	 m_keyBackward= keyBackward;
	 m_keyRotationLeft= keyRotationLeft;
	 m_keyRotationRight= keyRotationRight;
}

ObjectMovement::~ObjectMovement()
{
}

void ObjectMovement::Start()
{
}

void ObjectMovement::Update()
{
	
	if (sf::Keyboard::isKeyPressed(m_keyLeft))
	{
		
		glm::vec3 position = m_gameObject->GetTransform()->GetPosition();
		position.x -= 0.1f;
		m_gameObject->GetTransform()->SetPosition(position);

	}

	if (sf::Keyboard::isKeyPressed(m_keyRight))
	{

		glm::vec3 position = m_gameObject->GetTransform()->GetPosition();
		position.x += 0.1f;
		m_gameObject->GetTransform()->SetPosition(position);

	}

	if (sf::Keyboard::isKeyPressed(m_keyForward))
	{

		glm::vec3 position = m_gameObject->GetTransform()->GetPosition();
		position.z -= 0.1f;
		m_gameObject->GetTransform()->SetPosition(position);

	}

	if (sf::Keyboard::isKeyPressed(m_keyBackward))
	{

		glm::vec3 position = m_gameObject->GetTransform()->GetPosition();
		position.z += 0.1f;
		m_gameObject->GetTransform()->SetPosition(position);

	}


	if (sf::Keyboard::isKeyPressed(m_keyRotationLeft))
	{

		glm::vec3 rotation = m_gameObject->GetTransform()->GeRotation();
		rotation.y -= 0.1f;
		m_gameObject->GetTransform()->SetRotation(rotation);

	}

	if (sf::Keyboard::isKeyPressed(m_keyRotationRight))
	{

		glm::vec3 rotation = m_gameObject->GetTransform()->GeRotation();
		rotation.y += 0.1f;
		m_gameObject->GetTransform()->SetRotation(rotation);

	}
}
