#pragma once
#ifndef GAME_OBJECT
#define GAME_OBJECT
#include "Engine.h"

#include <vector>
#include <string>


class Engine;
class Render3D;
class Transform3D;
class Component;


class GameObject
{
public:
	GameObject(Engine * engine,std::string name);
	~GameObject();

	void Start();
	void Update();
	void Render();
	void End();

	void AddComponent(Component *component);

	Engine * GetEngine();
	Transform3D * GetTransform();
	template<typename T> T * GetComponent();

	
	

protected : 
	Engine * m_engine;
	Render3D * m_render3D;
	Transform3D * m_transform;
	std::vector<Component*> m_components;
	std::string m_name;


	
};
/*template<typename T> inline T * GameObject::GetComponent()
{
	Component * result = NULL;
	for (int i = 0; i < m_components.size(); i++) {
		T * testObject = dynamic_cast<T*>();
		if (testObject != NULL) {
			result = testObject;
			break;
		}
	}

	return result;
}*/

#endif // !

template<typename T>
inline T * GameObject::GetComponent()
{
	T * result = NULL;
	for (int i = 0; i < m_components.size(); i++) {
		T * testObject = dynamic_cast<T*>(m_components[i]);
		if (testObject != NULL) {
			result = testObject;
			break;
		}
	}

	return result;
}
