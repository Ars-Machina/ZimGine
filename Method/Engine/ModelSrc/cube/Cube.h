#ifndef CUBE_H
#define CUBE_H

#include "../../Model/Model.h"
#include "../../Mesh/Mesh.h"


class Cube{
public:
	Cube(float size, vec3 position);
	~Cube();
	void Draw(Shader* shader);
	float getSize();
	vec3 getPos();
	void setSize(float newSize);
	void setPos(vec3 newPos);
	void setVelocity(vec3 newV);
	vec3 getVelocity();
	vector<Vertex> getVertices();
	Mesh getMesh();
private:
	void setupMesh();
	float size;
	vec3 position;
	Model cubeModel = Model("Engine/Modelsrc/cube/cube.3ds");
	double mass;
	double weight;
	vec3 velocity;
};

#endif