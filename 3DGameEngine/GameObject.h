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

protected : 
	Engine * m_engine;
	Render3D * m_render3D;
	Transform3D * m_transform;
	std::vector<Component*> m_components;
	std::string m_name;


	
};
#endif // !
