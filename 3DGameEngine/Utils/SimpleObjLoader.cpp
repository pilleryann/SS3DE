#include "SimpleObjLoader.h"



SimpleObjLoader::SimpleObjLoader()
{
}


SimpleObjLoader::~SimpleObjLoader()
{
}

bool SimpleObjLoader::loadOBJ(const char * path, std::vector<glm::vec3>& out_vertice, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1) {
		char lineHeader[128];//Condidérons que le header de la ligne  ne fait pas plus de 128 byte
		int res = fscanf(file, "%s", lineHeader);//lisons le premier mot de la ligne.
		if (res == EOF)
			break;


		//On récupère les sommets 
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		//On récupère les UV 
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f \n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		//On récupère les normals 
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f \n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		//On récupère les faces 
		else if (strcmp(lineHeader, "f") == 0) {
			/**	La partie face contient trois bloques de 3 indices. ==> sommet des triangles
				Chaqu'un des indices de ce bloque ont la sigification suivante :
					1. Indice d'accès aux coordonnées du sommet
					2. Indice d'accès aux coordonnées UV du sommet
					3. Indice d'accès à la normal du sommet 
				Contrairment au C++, les indices commencent par 1 et non pas par 0.
				**/
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("Le fichier ne peut être lu par le parser simple : Essayez de modififier les paramètres d'export de Blender.");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}

		/* Opération d'indexation 
			On va transformer ces informations avec des indices en informations qui sont au format 
			qu'OpenGL puisse lire.
		*/
		

		
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertexPosition = temp_vertices[vertexIndex - 1]; // Ne pas oublier que dans OBJ les indices commencent par 1
		out_vertice.push_back(vertexPosition);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uvPosition = temp_uvs[uvIndex - 1]; // Ne pas oublier que dans OBJ les indices commencent par 1
		out_uvs.push_back(uvPosition);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1]; // Ne pas oublier que dans OBJ les indices commencent par 1
		out_normals.push_back(normal);
	}

	return true;
}
