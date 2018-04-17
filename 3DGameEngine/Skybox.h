#pragma once
#ifndef SKYBOX
#define SKYBOX

#include "glm\glm.hpp"
#include "GameObject.h"


class CubeMapTexture;
class SkyboxMaterial;
class Skybox :GameObject
{

public:
	Skybox(Engine * engine);
	~Skybox();



	glm::vec3 GetEnvironnentColor();

private :
	CubeMapTexture * m_cubeMap;
	SkyboxMaterial * m_skyboxMaterial;


};

#endif // !SKYBOX