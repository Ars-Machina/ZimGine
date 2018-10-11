#ifndef MESH_H
#define MESH_H

#include "../include.h"
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
	void DrawText(Shader shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif