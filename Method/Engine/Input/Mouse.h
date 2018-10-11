#ifndef MOUSE_H
#define MOUSE_H

#include "../include.h"
#include "..\Camera\Camera.h"


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