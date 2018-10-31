#ifndef OBJECT_H
#define OBJECT_H

#include "../include.h"
#include "../Shader/Shader.h"
#include "../Model/Model.h"

class Object {
private:
	vec3 rotation;
	vec3 velocity;
	vec3 position;
	int size;
	Model objectModel;
	float yMax, yMin, xMax, xMin, zMax, zMin;
	void getBounds();
public:
	Object();
	Object(int objectType);
	Object(const char* filename);
	void Draw(Shader &shader);
	void setPos(vec3 newPos);
	void setVelocity(vec3 newVelocity);
	void setRotation(vec3 newRotation);
	void setSize(int newSize);
	void printObjectBounds();
};

#endif