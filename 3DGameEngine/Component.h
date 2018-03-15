#pragma once
#ifndef COMPONENT
#define COMPONENT

class GameObject;

class Component
{


public:
	Component(GameObject * gameObject);
	~Component();

	virtual void Start()=0;
	virtual void Update()=0;

	
protected:

	GameObject * m_gameObject;



};


#endif
