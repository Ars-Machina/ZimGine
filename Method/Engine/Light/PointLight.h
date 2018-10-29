#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "../include.h"
#include "..\Shader\Shader.h"

using namespace std;
using namespace glm;

class PointLight {
public:
	PointLight(vec3 pos, int inputID);
	void Draw(Shader* shader);
	void Draw2(Shader* shader, mat4 view, mat4 projection, mat4 model);
	unsigned int getVAO();
	void setPosition(vec3 pos);
private:
	unsigned int VAO, VBO;
	int id;
	void setup();
	vec3 position;
};

#endif