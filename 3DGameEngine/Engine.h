#pragma once

#ifndef GAME_ENGINE
#define GAME_ENGINE
#include "GL\glew.h"
#include <SFML/Graphics.hpp>

#include <vector>

class Camera;
class GameObject;
class LightComponent;
class Skybox;

class Engine
{
public:
	Engine();
	~Engine();

	int Init();
	int CreateScene();
	int Run();
	int End();
	Camera * GetMainCamera();
	void SetMainCamera(Camera * camera);
	std::vector<LightComponent*>* getLightsInScene();
	

private :
	sf::Window * window;
	Camera * m_mainCamera;
	std::vector<GameObject*> gameObjects;
	GLuint VertexArrayID;
	std::vector<LightComponent*> m_lightsList;
	Skybox * m_skybox;

};
#endif
