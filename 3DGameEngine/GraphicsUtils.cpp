#include "GraphicsUtils.h"



GraphicsUtils::GraphicsUtils()
{
}


GraphicsUtils::~GraphicsUtils()
{
}

void GraphicsUtils::computeTangentBasis(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals, std::vector<glm::vec3>& tangents, std::vector<glm::vec3>& bitangents)
{

	for (int i = 0; i < vertices.size(); i += 3) {

		// Shortcuts for vertices
		glm::vec3 & v0 = vertices[i + 0];
		glm::vec3 & v1 = vertices[i + 1];
		glm::vec3 & v2 = vertices[i + 2];

		// Shortcuts for UVs
		glm::vec2 & uv0 = uvs[i + 0];
		glm::vec2 & uv1 = uvs[i + 1];
		glm::vec2 & uv2 = uvs[i + 2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		/**Cette formule est le résultat de l'equation suivante :
		En sachant que E1 et E2 représentent les vecteurs des côté du polygone
		DeltaUV1 et DeltaUV2 sont les côtés des coordonnées UV du même polygone
		T est un vecteur tangente au polygone et est perpendiculaire au vecteur normal (N)
		B est un vecteur bitangente au polygone et est perpendiculaire au vecteur normal (N) et T
		Nous considéront les vecteurs T et B comme les bases orthonormaux des coordonnée UV qui permettent de décrire les vectuer E1 et E2
			E1 = deltaUV1.x * T + deltaUV1.y * B
			E2 = deltaUV2.x * T + deltaUV2.y * B

		Pour caculer cela on peut transformer cela en matrices :

			E = deltaUV * TB
		Et nous appliquons l'équation en extrayant la matrice deltaUV
			deltaUV^2 * E = TB
		Cela donne les formules ci-dessous.

		**/
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;


		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later, in vboindexer.cpp
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		// Same thing for binormals
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);

	}
}
