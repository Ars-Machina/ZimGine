#ifndef MESH_H
#define MESH_H

#include "../include.h"
#include <stdlib.h>
#include "..\Shader\Shader.h"

using namespace std;
using namespace glm;

struct Vertex {
	vec3 Position = vec3(0.0);
	vec3 Normal = vec3(0.0);
	vec2 TexCoords = vec2(0.0);
	vec3 Tangent = vec3(0.0);
	vec3 Bitangent = vec3(0.0);
};

struct Texture {
	unsigned int id = NULL;
	string type = "NULL";
	string path = "NULL";
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
	void DrawText(Shader shader);
	void SaveToFile(const char* fileName);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
	int id;
};

#endif