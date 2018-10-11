#ifndef DIRLIGHT_H
#define DIRLIGHT_H
#include "..\Shader\Shader.h"
#include "../include.h"

class DirLight {
public:
	DirLight();
	void Draw(Shader* shader);
private:
	void setup();
	unsigned int VAO, VBO;
};

#endif