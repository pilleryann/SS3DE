#pragma once

#ifndef GAME_ENGINE
#define GAME_ENGINE
#include "GL\glew.h"
#include <SFML/Graphics.hpp>

#include <vector>

class Camera;
class GameObject;

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
private :
	sf::Window * window;
	Camera * m_mainCamera;
	std::vector<GameObject*> gameObjects;
	GLuint VertexArrayID;

};
#endif
