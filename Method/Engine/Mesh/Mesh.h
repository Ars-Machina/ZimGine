#ifndef MESH_H
#define MESH_H

#include "GL/glew.h"
#define GLEW_STATIC
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "..\Shader\Shader.h"

using namespace std;
using namespace glm;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
	vec3 Tangent;
	vec3 Bitangent;
};

struct Texture {
	unsigned int id = NULL;
	string type;
	string path;
};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh();
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	~Mesh();
	void Draw(Shader shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif