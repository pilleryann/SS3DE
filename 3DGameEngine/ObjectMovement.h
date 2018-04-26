#pragma once
#include "Component.h"
#include <SFML\Window.hpp>
class ObjectMovement :
	public Component
{
public:
	ObjectMovement(GameObject * gameObject,sf::Keyboard::Key keyLeft = sf::Keyboard::A,
		sf::Keyboard::Key keyRight = sf::Keyboard::D, sf::Keyboard::Key keyForward = sf::Keyboard::W,
		sf::Keyboard::Key keyBackward = sf::Keyboard::S, sf::Keyboard::Key keyRotationLeft = sf::Keyboard::Left,
		sf::Keyboard::Key keyRotationRight = sf::Keyboard::Right );
	~ObjectMovement();

	 void Start();
	 void Update();


private :
	sf::Keyboard::Key m_keyLeft;
	sf::Keyboard::Key m_keyRight;
	sf::Keyboard::Key m_keyForward;
	sf::Keyboard::Key m_keyBackward;
	sf::Keyboard::Key m_keyRotationLeft;
	sf::Keyboard::Key m_keyRotationRight;
};

