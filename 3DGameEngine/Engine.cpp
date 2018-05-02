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

#include "TextureCamera.h"
#include "PostProcessingMaterial.h"



int main(void) {
	fprintf(stdout, "Start Game Engine 3D  !\n");
	//getchar();

	Engine engine;

	engine.Init();
	engine.CreateScene();
	engine.initPostProcessingRendering();
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

	//glClearColor(0.4f, 0.0f, 0.0f, 0.0f);

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
	cameraGo->GetTransform()->SetPosition(glm::vec3(0, 0, 10));
	cameraGo->GetTransform()->SetRotation(glm::vec3(0,0,0));
	ObjectMovement * objMovCam = new ObjectMovement(cameraGo);
	cameraGo->AddComponent(objMovCam);
	gameObjects.push_back(cameraGo);

	
	GameObject * lightObject = new GameObject(this, "Point light");
	LightComponent * lightComponent = new LightComponent(lightObject, glm::vec3(2, 2,1), 10, glm::vec3(1, 1, 1));
	lightObject->AddComponent(lightComponent);
	gameObjects.push_back(lightObject);

	//camera->LookAt(glm::vec3(1,0.0f,0), glm::vec3(0, 1,0));

	
	GameObject * go = new GameObject(this, "First object");
	BasicMaterialTest * mat = new BasicMaterialTest(go, "Datas/StoneWallTextures/StoneWallCOLOR.png", "Datas/StoneWallTextures/StoneWallNORM.png");
	Mesh * mesh = new Mesh("Datas/Sphere3.obj");
	Render3D * render = new Render3D(go,mesh,mat);
	go->AddComponent(render);
	go->GetTransform()->SetScale(glm::vec3(1, 1,1));
	go->GetTransform()->SetPosition(glm::vec3(0, 0,20));
	go->GetTransform()->SetRotation(glm::vec3(0, 0, 0));
	

	gameObjects.push_back(go);
	
	//camera->LookAt(go->GetTransform()->GetPosition(), glm::vec3(0, 1, 0));
	

	//camera->LookAt(glm::vec3(0,0,0), glm::vec3(0, 3, 0));
	
	GameObject * go3 = new GameObject(this, "Third object");
	BasicMaterialTest * mat3 = new BasicMaterialTest(go3, "Datas/DirtTexture/Dirt_004_COLOR.JPG", "Datas/DirtTexture/Dirt_004_NORM.jpg");
	Mesh * mesh3 = new Mesh("Datas/Sphere3.obj");
	Render3D * render3 = new Render3D(go3,mesh3,mat3);
	go3->AddComponent(render3);
	go3->GetTransform()->SetScale(glm::vec3(2,2,2));
	go3->GetTransform()->SetPosition(glm::vec3(-2, 0, 1));
	go3->GetTransform()->SetRotation(glm::vec3(0, 0, 0));

	/*ObjectMovement * objMov = new ObjectMovement(go3);
	go3->AddComponent(objMov);*/

	gameObjects.push_back(go3);

	//camera->LookAt(glm::vec3(1,0,1), glm::vec3(0, 1, 0));
	
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
		firstPassRendering();
		secondPassRenderingPostProcessing();
	//	sceneRendering();
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

	void Engine::initPostProcessingRendering()
	{

		m_textureCamera = new TextureCamera(800, 600);
		m_postProcessingMaterial = new PostProcessingMaterial(nullptr, m_textureCamera);
		m_meshPlanPostProcessing = new Mesh("Datas/postProcessingPlan.obj");
		m_meshPlanPostProcessing->Init();
		m_postProcessingMaterial->InitMaterial();
	}

	void Engine::sceneRendering()
	{
		for (int i = 0; i<gameObjects.size(); i++) {
			gameObjects[i]->Render();
		}
	}

	void Engine::firstPassRendering()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_textureCamera->GetFrameBufferID());
		glClearColor(1.0f,0.0f, 0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		sceneRendering();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	void Engine::secondPassRenderingPostProcessing()
	{
		
	//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		m_postProcessingMaterial->SetMaterialToRender();
		

		//fprintf(stdout, "Draw!\n");
		//On applique l'ID d'attribut de vertex à 0. Dans le shader on peur le récupérer avec "location".
		glEnableVertexAttribArray(0);//Ouverture edtion buffer sur l'attribut ID = 0. On décide que cela correspond au couleur des vertex.
		glBindBuffer(GL_ARRAY_BUFFER, m_meshPlanPostProcessing->GetVertexArrayID());//Choix du buffer
		glVertexAttribPointer(
			0, // Attribuer un layer ==> pour shader. 0 est un choix arbitraire
			3, // size
			GL_FLOAT, //type
			GL_FALSE, // normalized 
			0, // stride
			(void*)0 //Array buffer offset
		);


		//--------- Ajouter l'attribut des couleurs sur les vertex-----------


		glEnableVertexAttribArray(1);//Ouverture edtion buffer sur l'attribut ID = 0. On décide que cela correspond au couleur des vertex.
		glBindBuffer(GL_ARRAY_BUFFER, m_meshPlanPostProcessing->GetNormalsArrayID());//Choix du buffer
		glVertexAttribPointer(
			1, // Attribuer un layer ==> pour shader. 0 est un choix arbitraire
			3, // size
			GL_FLOAT, //type
			GL_FALSE, // normalized 
			0, // stride
			(void*)0 //Array buffer offset
		);


		// Ajouter l'attribut UV
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_meshPlanPostProcessing->GetUVArrayID());
		glVertexAttribPointer(
			2,
			2,//Size ==> coordonnees 2 dimensions pour les UV 
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

	//	glDrawArrays(GL_TRIANGLES, 0, m_meshPlanPostProcessing->GetVertexArraySize());
		glDrawArrays(GL_TRIANGLES, 0, m_meshPlanPostProcessing->GetVertexArraySize());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindTexture(GL_TEXTURE_2D,0);
	}

