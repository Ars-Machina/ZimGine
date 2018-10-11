#include "Cube.h"

double getVelocityFunc(double time) {
	return -9.81*time;
}

Cube::Cube(float size, vec3 position) {
	this->position = position;
	this->size = size;
	mass = 100.0;
	weight = mass * 9.81;
	velocity = vec3(0);
	setupMesh();
}

Cube::~Cube() {
}

void Cube::setupMesh() {
	cubeModel = Model("Engine/Modelsrc/cube/cube.3ds");
}

void Cube::Draw(Shader* shader) {
	mat4 model = mat4(1.0f);
	model = scale(model, vec3(size));
	model = translate(model, vec3(position));
	double time = glfwGetTime();
	if (position.y<-5 && velocity.y > -20){
		velocity.y = 0;
		position.y = -5;
	}
	else {
		velocity.y += getVelocityFunc(time) / 10000;
		position.y += velocity.y;
	}
	shader->setMat4("model", model);
	cubeModel.Draw(*shader);
}

float Cube::getSize() {
	return size;
}

void Cube::setSize(float newSize) {
	size = newSize;
}

vec3 Cube::getPos() {
	return position;
}

void Cube::setPos(vec3 newPos) {
	position = newPos;
}

vector<Vertex> Cube::getVertices() {
	vector<Vertex> vertices;
	for (int i = 0; i < cubeModel.getMeshes().size(); i++) {
		for (int j = 0; j < cubeModel.getMeshes()[i].vertices.size(); j++) {
			vertices.push_back(cubeModel.getMeshes()[i].vertices[j]);
		}
	}
	return vertices;
}

void Cube::setVelocity(vec3 newV) {
	velocity = newV;
}

vec3 Cube::getVelocity() {
	return velocity;
}