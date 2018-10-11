#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "GL/glew.h"
#define GLEW_STATIC
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "..\Shader\Shader.h"

using namespace std;
using namespace glm;

class PointLight {
public:
	PointLight(vec3 pos);
	void Draw(Shader* shader);
	void Draw2(Shader* shader, mat4 view, mat4 projection, mat4 model);
	unsigned int getVAO();
	void setPosition(vec3 pos);
private:
	unsigned int VAO, VBO;
	void setup();
	vec3 position;
};

#endif