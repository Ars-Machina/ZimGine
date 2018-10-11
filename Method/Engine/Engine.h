#ifndef ENGINE_H
#define ENGINE_H

#include "GL/glew.h"
#define GLEW_STATIC
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader/Shader.h"
#include "Camera/Camera.h"
#include "Light/DirLight.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"
#include "Input/Mouse.h"
#include "ModelSrc/Triangle/Triangle.h"
#include "World/FloorPlane.h"
#include "ModelSrc/cube/Cube.h"
#include <iostream>
using namespace std;

class Engine {
private:
	Camera* camera;
	GLFWwindow* window;
	Shader* shader;
	Mouse* mainMouse;
public:
	Engine();
	bool Init(const char* title);
	bool createShaders();
	void Update();
	void BeginRender(vec3);
	void EndRender();
	void setShaderMains(Camera* camera1, Shader* shade);
	GLFWwindow* getWindow();
	Shader* getShader();
	Camera* getCam();
};

#endif
