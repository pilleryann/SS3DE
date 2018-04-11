#include "ObjectMovement.h"
#include <SFML\Window.hpp>
#include "GameObject.h"
#include "Transform3D.h"
#include "glm\glm.hpp"



ObjectMovement::ObjectMovement(GameObject * gameObject):Component(gameObject)
{
}

ObjectMovement::~ObjectMovement()
{
}

void ObjectMovement::Start()
{
}

void ObjectMovement::Update()
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		
		glm::vec3 position = m_gameObject->GetTransform()->GetPosition();
		position.x -= 0.1f;
		m_gameObject->GetTransform()->SetPosition(position);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{

		glm::vec3 position = m_gameObject->GetTransform()->GetPosition();
		position.x += 0.1f;
		m_gameObject->GetTransform()->SetPosition(position);

	}
}
