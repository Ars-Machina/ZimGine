#ifndef CAMERA_H
#define CAMERA_H

#include "GL/glew.h"
#define GLEW_STATIC
#include "..\Shader\Shader.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
using namespace glm;

class Camera {
public:
	float sensitivity = 0.1f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	Shader shader;
	vec3 camPos;
	vec3 camTarget;
	vec3 camDirection;
	vec3 up;
	vec3 camRight;
	vec3 camUp;
	vec3 camFront;
	float zoom;

	Camera();
	Camera(Shader*, vec3);
	mat4 getViewMatrix();
	void processMouseMovement(float yawF, float pitchF);
};

#endif