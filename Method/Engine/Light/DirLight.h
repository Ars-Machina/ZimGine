#ifndef DIRLIGHT_H
#define DIRLIGHT_H
#include "..\Shader\Shader.h"
#include "GL/glew.h"
#define GLEW_STATIC
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class DirLight {
public:
	DirLight();
	void Draw(Shader* shader);
private:
	void setup();
	unsigned int VAO, VBO;
};

#endif