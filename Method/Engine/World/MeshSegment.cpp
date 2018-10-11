#include "MeshSegment.h"

MeshSegment::MeshSegment(vec3 pos) {
	position = pos;
	setupMesh();
}

void MeshSegment::setupMesh() {
	Vertex v1, v2, v3, v4;
	v1.Position = vec3(1.0f, 0.0f, 1.0f)+position;
	v2.Position = vec3(1.0f, 0.0f, -1.0f)+position;
	v3.Position = vec3(-1.0f, 0.0f, 1.0f)+position;
	v4.Position = vec3(-1.0f, 0.0f, -1.0f)+position;
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	indices = {
		1,2,3,
		4,2,3
	};
	Texture tex1;
	tex1.id = TextureFromFile("crystal1.jpeg", "Engine/World");
	tex1.type = "texture_diffuse";
	tex1.path = "crystal1.jpeg";
	textures.push_back(tex1);
}

MeshSegment::~MeshSegment() {
	
}

void MeshSegment::Draw(Shader* shader) {
	Mesh meshSeg = Mesh(vertices, indices, textures);
	mat4 model = mat4(0.0f);
	model = translate(model, position);
	meshSeg.Draw(*shader);
}

vector<Vertex> MeshSegment::getVert() {
	return vertices;
}

vector<unsigned int> MeshSegment::getIndex() {
	return indices;
}

vector<Texture> MeshSegment::getTex() {
	return textures;
}