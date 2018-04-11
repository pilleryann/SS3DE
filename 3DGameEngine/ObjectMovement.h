#pragma once
#include "Component.h"
class ObjectMovement :
	public Component
{
public:
	ObjectMovement(GameObject * gameObject);
	~ObjectMovement();

	 void Start();
	 void Update();


	
};

