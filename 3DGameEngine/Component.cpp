#include "Component.h"
#include "GameObject.h"





Component::Component(GameObject * gameObject):m_gameObject(gameObject)
{
}

Component::~Component()
{
}
