#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "../include.h"
#include "..\Shader\Shader.h"

class SpotLight {
public:
	SpotLight(vec3 pos, vec3 dir);
	void DrawObject(Shader* shader, mat4 view, mat4 projection, mat4 model);
	void DrawLight(Shader* shader);
	void setPosition(vec3 pos);
	void setDirection(vec3 dir);
private:
	void setup();
	unsigned int VAO, VBO;
	vec3 position, direction;
};

#endif