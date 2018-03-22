#pragma once
#ifndef GRAPHICS_UTILS
#define GRAPHICS_UTILS
#include "glm\glm.hpp"
#include <vector>

class GraphicsUtils
{
public:
	GraphicsUtils();
	~GraphicsUtils();

	static void computeTangentBasis(
		//inputs
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals,
		
		//output
		std::vector<glm::vec3> & tangents,
		std::vector<glm::vec3> & bitangents
	);
};

#endif // !GRAPHICS_UTILS