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
	calculateVelocityDefault();
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
	calculateVelocityDefault();
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

void Camera::calculateVelocityDefault() {
	velocity = vec3(0.0f);
	defaultAccel = 0.1f;
	slowDownRate = -0.05f;
	speedScalar = 0.0f;
	vNormal = normalize(velocity);
}

void Camera::changeVelocity(char key) {
	if (speedScalar < 0.3) {
		if (key == 'w') {
			velocity = camFront;
			vNormal = normalize(velocity);
			camPos += vNormal * vec3(0.0f + speedScalar, 0.0f + speedScalar, 0.0f + speedScalar);
			speedScalar += defaultAccel;
		}
		if (key == 's') {
			velocity = -camFront;
			vNormal = normalize(velocity);
			camPos += vNormal * vec3(0.0f + speedScalar,0.0f + speedScalar, 0.0f + speedScalar);
			speedScalar += defaultAccel;
		}
		if (key == 'a') {
			velocity = cross(camUp, camFront);
			vNormal = normalize(velocity);
			camPos += vNormal * vec3(0.0f + speedScalar, 0.0f + speedScalar, 0.0f + speedScalar);
			speedScalar += defaultAccel;
		}
		if (key == 'd') {
			velocity = -cross(camUp, camFront);
			vNormal = normalize(velocity);
			camPos += vNormal * vec3(0.0f + speedScalar, 0.0f + speedScalar, 0.0f + speedScalar);
			speedScalar += defaultAccel;
		}
	}
	if (key == 'i') {
		if (speedScalar > 0) {
			camPos += vNormal * vec3(0.0f + speedScalar, 0.0f + speedScalar, 0.0f + speedScalar);
			speedScalar += slowDownRate;
		}
	}
}