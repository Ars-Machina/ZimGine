#include "Camera.h"

Camera::Camera() {
	camPos = vec3(0.0f, 0.0f, 0.0f);
	camTarget = vec3(0.0f, 0.0f, 1.0f);
	camDirection = normalize(camPos - camTarget);
	up = vec3(0.0f, 1.0f, 0.0f);
	camRight = normalize(cross(up, camDirection));
	camUp = vec3(0.0f, 1.0f, 0.0f);
	camFront = vec3(0.0f, 0.0f, 1.0f);
	zoom = radians(90.0f);
}

Camera::Camera(Shader* shader, vec3 position) {
	camPos = position;
	camTarget = vec3(0.0f, 0.0f, 0.0f);
	camDirection = normalize(camPos - camTarget);
	up = vec3(0.0f, 1.0f, 0.0f);
	camRight = normalize(cross(up, camDirection));
	camUp = vec3(0.0f, 1.0f, 0.0f);
	camFront = vec3(0.0f, 0.0f, 1.0f);
	zoom = radians(90.0f);
}

mat4 Camera::getViewMatrix() {
	return lookAt(camPos, camPos + camFront, camUp);
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	vec3 front;
	front.x = cos(radians(yaw))*cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw))*cos(radians(pitch));
	camFront = normalize(front);
}