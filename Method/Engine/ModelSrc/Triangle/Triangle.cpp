#include "Triangle.h"

Triangle::Triangle(vec3 position) {
	this->position = position;
	setupMesh();
}

void Triangle::setupMesh() {
	Vertex v1;
	Vertex v2;
	Vertex v3;
	v1.Position = vec3(-1.0f, -1.0f, 0.0f);
	v1.TexCoords = vec2(0.0f);
	v1.Normal = vec3(1.0f);
	v2.Position = vec3(1.0f, -1.0f, 0.0f);
	v2.TexCoords = vec2(0.0f);
	v2.Normal = vec3(1.0f);
	v3.Position = vec3(0.0f, 1.0f, 0.0f);
	v3.TexCoords = vec2(0.0f);
	v3.Normal = vec3(1.0f);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	indices = {
		1,3,2
	};
	Texture tex1;
	tex1.type = "texture_diffuse";
	tex1.path = "../../Textures/Brick1.jpg";
	tex1.id = TextureFromFile("Brick1.jpg", "Engine/Textures");
	textures.push_back(tex1);
	model = translate(mat4(1.0f), position);
}

void Triangle::Draw(Shader* shader) {
	shader->setMat4("model", model);
	Mesh mesh = Mesh(vertices, indices, textures);
	mesh.Draw(*shader);
}