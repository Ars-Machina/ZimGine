#include "Mouse.h"

Mouse::Mouse(Camera* cam) {
	camera = cam;
}

void Mouse::processInput(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = (float)xPos;
		lastY = (float)yPos;
		firstMouse = false;
	}
	float xoffset = (float)(xPos - lastX);
	float yoffset = (float)(lastY - yPos);
	lastX = (float)xPos;
	lastY = (float)yPos;
	camera->processMouseMovement(xoffset, yoffset);
}