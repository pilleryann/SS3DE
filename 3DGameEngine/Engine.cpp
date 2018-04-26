#include "Engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "GameObject.h"
#include "Render3D.h"
#include "Transform3D.h"
#include "Camera.h"
#include "ObjectMovement.h"
#include "Skybox.h"

#include "LightComponent.h"

#include "BasicMaterialTest.h"
#include "Mesh.h"

#include <SFML/Graphics.hpp>




int main(void) {
	fprintf(stdout, "Start Game Engine 3D  !\n");
	//getchar();

	Engine engine;

	engine.Init();
	engine.CreateScene();
	engine.Run();
	engine.End();
	return 0;
}



Engine::Engine()
{
}


Engine::~Engine()
{
	delete window;
}


/*
	Init the engine and create the scene.
*/
int Engine::Init()
{

	fprintf(stdout, "Init Game Engine 3D\n");

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = 5;
	

	window = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);

	
	window->setVerticalSyncEnabled(true);

	// activation de la fenêtreTranslated previous changes of the OpenGL tutorial
	window->setActive(true);


	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		// Problem: glewInit failed, something is seriously wrong.
		std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
		exit(1);
	}

	// Créer VAO ==> context objet. On peut regrouper les data et attribute pour éviter de faire 100 appelle par objet ==> optimisation
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);



	//-----Partie Z BUFFER -----
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//Partie enlever backface 
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	//--- Partie Object ----

	glClearColor(0.4f, 0.0f, 0.0f, 0.0f);

	// chargement des ressources, initialisation des états OpenGL, ...

	
	return 0;

}

int Engine::CreateScene()
{
	m_skybox = new Skybox(this);
	gameObjects.push_back((GameObject*)m_skybox);

	GameObject * cameraGo = new GameObject(this,"Main Camera");
	Camera * camera = new Camera(cameraGo,glm::vec2(800,600),0.1f,1000.0f,60.0f);
	cameraGo->AddComponent(camera);
	cameraGo->GetTransform()->SetPosition(glm::vec3(0, 0, 3));
	cameraGo->GetTransform()->SetRotation(glm::vec3(0, 0,0));
	
	gameObjects.push_back(cameraGo);


	GameObject * lightObject = new GameObject(this, "Point light");
	LightComponent * lightComponent = new LightComponent(lightObject, glm::vec3(2, 2,1), 10, glm::vec3(1, 1, 1));
	lightObject->AddComponent(lightComponent);
	/*BasicMaterialTest * mat2 = new BasicMaterialTest(lightObject, "Datas/DirtTexture/Dirt_004_COLOR.JPG", "Datas/DirtTexture/Dirt_004_NORM.jpg");
	Mesh * mesh2 = new Mesh("Datas/Sphere3.obj");
	Render3D * render2 = new Render3D(lightObject, mesh2, mat2);
	lightObject->AddComponent(render2);*/
	gameObjects.push_back(lightObject);

	
	GameObject * go = new GameObject(this, "First object");
	BasicMaterialTest * mat = new BasicMaterialTest(go, "Datas/StoneWallTextures/StoneWallCOLOR.png", "Datas/StoneWallTextures/StoneWallNORM.png");
//	BasicMaterialTest * mat = new BasicMaterialTest(go,albedoPath, normalPath);
	Mesh * mesh = new Mesh("Datas/Sphere3.obj");
	Render3D * render = new Render3D(go,mesh,mat);
	go->AddComponent(render);
	go->GetTransform()->SetScale(glm::vec3(1, 1,1));
	go->GetTransform()->SetPosition(glm::vec3(0, 0,0));
	go->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	ObjectMovement * objMov = new ObjectMovement(go);
	go->AddComponent(objMov);

	gameObjects.push_back(go);
	
	camera->LookAt(go->GetTransform()->GetPosition(), glm::vec3(0, 1, 0));


	//camera->LookAt(glm::vec3(0,0,0), glm::vec3(0, 3, 0));
	
	GameObject * go3 = new GameObject(this, "Third object");
	BasicMaterialTest * mat3 = new BasicMaterialTest(go3, "Datas/DirtTexture/Dirt_004_COLOR.JPG", "Datas/DirtTexture/Dirt_004_NORM.jpg");
	//	BasicMaterialTest * mat = new BasicMaterialTest(go,albedoPath, normalPath);
	Mesh * mesh3 = new Mesh("Datas/Sphere3.obj");
	Render3D * render3 = new Render3D(go3,mesh3,mat3);
	go3->AddComponent(render3);
	go3->GetTransform()->SetScale(glm::vec3(2,2,2));
	go3->GetTransform()->SetPosition(glm::vec3(-2, 0, 1));
	go3->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	gameObjects.push_back(go3);


	/*
	GameObject * go = new GameObject(this, "First object");
	Render3D * render = new Render3D(go);
	go->AddComponent(render);
	go->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	go->GetTransform()->SetPosition(glm::vec3(5, 1, 1));
	go->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	gameObjects.push_back(go);

	
	GameObject * go2 = new GameObject(this, "Second object");
	Render3D * render2 = new Render3D(go2);
	go2->AddComponent(render2);
	go2->GetTransform()->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
	go2->GetTransform()->SetPosition(glm::vec3(0, 0, 0));
	go2->GetTransform()->SetRotation(glm::vec3(90, 0, 0));
	gameObjects.push_back(go2);

	GameObject * go3 = new GameObject(this, "Third object");
	Render3D * render3 = new Render3D(go3);
	go3->AddComponent(render3);
	go3->GetTransform()->SetScale(glm::vec3(3.0f, 3.0f, 3.0f));
	go3->GetTransform()->SetPosition(glm::vec3(2, 2, 0));
	go3->GetTransform()->SetRotation(glm::vec3(-60, 180, 0));
	gameObjects.push_back(go3);

	camera->LookAt(go3->GetTransform()->GetPosition(), glm::vec3(0, 1, 0));
	*/
	for (int i = 0;i< gameObjects.size(); i++) {
		gameObjects[i]->Start();
	}


	return 0;
}


/*
	Run the engine.
*/
int Engine::Run()
{
	
	// la boucle principale
	bool running = true;
	while (running)
	{
		// gestion des évènements
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// on stoppe le programme
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// on ajuste le viewport lorsque la fenêtre est redimensionnée
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		//Faire update des scripts
		for (int i = 0;i< gameObjects.size(); i++) {
			gameObjects[i]->Update();
		}

		// effacement les tampons de couleur/profondeur
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// dessin...
		for (int i = 0; i<gameObjects.size(); i++) {
			gameObjects[i]->Render();
		}

		// termine la trame courante (en interne, échange les deux tampons de rendu)
		window->display();
	}

	

	return 0;
}

/*
	Libarate the ressources 
*/
int Engine::End()
{
	glDeleteVertexArrays(1, &VertexArrayID);
	// libération des ressources...
	for (int i = 0; i<gameObjects.size(); i++) {
		delete gameObjects[i];
	}

	fprintf(stdout, "Fin de programme\n.");
	getchar();
	return 0;
}

	Camera * Engine::GetMainCamera()
	{
		return m_mainCamera;
	}

	void Engine::SetMainCamera(Camera * camera)
	{
		m_mainCamera = camera;
	}

	std::vector<LightComponent*>* Engine::getLightsInScene()
	{
		return &m_lightsList;
	}

