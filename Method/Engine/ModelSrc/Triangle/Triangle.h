#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../../Mesh/Mesh.h"
#include "../../Model/Model.h"

class Triangle {
public:
	Triangle(vec3 position);
	void Draw(Shader* shader);
private:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	void setupMesh();
	vec3 position;
	mat4 model;
};

#endif