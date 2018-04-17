#include "Skybox.h"
#include "Mesh.h"
#include "Render3D.h"
#include "SkyboxMaterial.h"
#include "CubeMapTexture.h"



Skybox::Skybox(Engine * engine):GameObject(engine,"Sky Box")
{
	Mesh * boxMesh = new Mesh("Datas/skyboxCube.obj");
	CubeMapTexture * cubeMap = new CubeMapTexture();
	SkyboxMaterial * skyBoxMat = new SkyboxMaterial(this, cubeMap);
	Render3D * render3D = new Render3D(this, boxMesh, skyBoxMat, true);
	AddComponent(render3D);
}

Skybox::~Skybox()
{
}


glm::vec3 Skybox::GetEnvironnentColor()
{
	return glm::vec3();
}
