#include "FloorPlane.h"

FloorPlane::FloorPlane(int size) {
	this->size = size;
	setupMesh();
}

FloorPlane::FloorPlane(int size, vec3 position) {
	this->size = size;
	this->position = position;
	setupMesh();
}

void FloorPlane::setupMesh() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			Vertex v;
			v.Position = vec3(i - 10, 0, j - 10);
			unsigned int index = (i * 10) + j;
			Texture tex1;
			tex1.id = TextureFromFile("Brick1.jpg", "Engine/Textures");
			tex1.path = "Engine/Textures/Brick1.jpg";
			tex1.type = "texture_diffuse";
			vertices.push_back(v);
			indices.push_back(index);
			textures.push_back(tex1);
		}
	}
}

void FloorPlane::Draw(Shader* shader) {
	Mesh mesh = Mesh(vertices, indices, textures);
	mesh.Draw(*shader);
}

void FloorPlane::setPos(vec3 newPos) {
	position = newPos;
	setupMesh();
}