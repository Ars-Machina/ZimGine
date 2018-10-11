#ifndef MOUSE_H
#define MOUSE_H
#include "GL/glew.h"
#define GLEW_STATIC
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "..\Camera\Camera.h"
#include <iostream>
using namespace std;

class Mouse {
public:
	Mouse(Camera* cam);
	void processInput(GLFWwindow* window, double xPos, double yPos);
private:
	Camera* camera;
	bool firstMouse = true;
	float lastX, lastY;
};

#endif