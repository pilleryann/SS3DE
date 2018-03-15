#pragma once
#ifndef TUTO_LOADER
#define TUTO_LOADER

#include<vector>


#include <glm/glm.hpp>
#include <glm/ext.hpp>
class SimpleObjLoader
{
public:
	SimpleObjLoader();
	~SimpleObjLoader();

	static bool loadOBJ(const char * path, std::vector < glm::vec3 > & out_vertice, std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals);
};

#endif
