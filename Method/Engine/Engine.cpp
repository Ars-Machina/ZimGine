#include "Engine.h"

using namespace glm;

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Engine::Engine() {
	
}

bool Engine::Init(const char* title) {

	//initialize GLFW
	glfwInit();

	//set the "settings" for GLFW right after initialization.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create the window to serve as our context
	window = glfwCreateWindow(1400, 900, title, NULL, NULL);

	//error check the window
	if (window == nullptr) {
		cout << "Window failed to initialize" << endl;
		return false;
	}

	//set the context to the window
	glfwMakeContextCurrent(window);

	//create a camera for us to manipulate
	camera = new Camera(shader, vec3(0.0f, 0.0f, -3.0f));

	//create the mouse object
	mainMouse = new Mouse(camera);

	//create an internal viewport based on pixel sizes
	glViewport(0, 0, 1400, 900);

	//a callback to change the framebuffer as the window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//how many times per frame the buffers will swap (1 is 1 time per frame)
	glfwSwapInterval(1);

	//initialize glew and enable experimental
	if (glewInit() == GLEW_OK) {
		cout << "Glew has initialized" << endl;
	}
	glewExperimental = true;

	//choose form of input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//set the mouse cursor callback
	glfwSetCursorPosCallback(window, mouse_callback);

	//set the mouse scrollwheel callback
	glfwSetScrollCallback(window, scroll_callback);

	//depth test
	glEnable(GL_DEPTH_TEST);

	return true;
}

void Engine::Update() {
	glfwPollEvents();
}

void Engine::BeginRender(vec3 lightLevel) {
	glClearColor(0.5f*lightLevel.x, 0.5f*lightLevel.y, 0.5f*lightLevel.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndRender() {
	glfwSwapBuffers(window);
}

GLFWwindow* Engine::getWindow() {
	return window;
}

bool Engine::createShaders() {
	shader = new Shader("Engine/Shader/vertexShader.txt", "Engine/Shader/fragmentShader.txt");
	return true;
}

Shader* Engine::getShader() {
	return shader;
}

Camera* Engine::getCam() {
	return camera;
}

void Engine::setShaderMains(Camera* camera1, Shader* shade) {
	mat4 view = camera1->getViewMatrix();
	mat4 projection = perspective(camera1->zoom, 16.0f / 9.0f, 0.1f, 100.0f);
	mat4 model = mat4(1.0f);
	model = scale(model, vec3(0.1f));
	shade->setVec3("viewPos", camera1->camPos);
	shade->setMat4("view", view);
	shade->setMat4("projection", projection);
	shade->setMat4("model", model);
}