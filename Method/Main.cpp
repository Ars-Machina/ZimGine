#include "Engine/Engine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Engine/Shader/stb_image.h"
#include "Engine/Mesh/Mesh.h"
#include "Engine/Model/Model.h"
#include "Engine/InputMode/InputMode.h"
#include "Engine/World/Collisions/Collisions.h"
#include "Engine/World/MeshSegment.h"

using namespace std;
using namespace glm;

void processInput(GLFWwindow* window, Camera* cam);
unsigned int loadTexture(const char *path);
Mesh loadMeshFromFile(const char* fileName);

bool wireframe = false;
float camSpeed = 0.05f;
float rotation = radians(2.0f);
unsigned int VAO, VBO, lightVAO, EBO;
vec4 myVec(1.0f, 0.0f, 0.0f, 1.0f);
mat4 trans(1.0f);
mat4 projection(1.0f);
mat4 model(1.0f);
mat4 view(1.0f);
vec3 lightColor(1.0f);
vec3 lightPos(1.0f);
vec3 worldColor(1.0f);
Camera* camUser;
bool firstMouse = true;
float lastX = 700;
float lastY = 450;
float yawF = 0;
float pitchF = 0;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
int mouseMode = CAMERA_MOVE;
int scrollMode = ZOOM;
int keyboardMode = CAMERA_TRANSLATE;
bool alreadyPressed = false;
bool tabPressed = false;
vector<MeshSegment> floors;
int i = 0;


int main() {
	
	Engine engine = Engine();
	bool initialized = engine.Init("title");
	if (initialized == false) {
		cout << "Engine Not Initialized" << endl;
		return -1;
	}
	engine.createShaders();
	camUser = engine.getCam();
	Mouse mainMouse = Mouse(engine.getCam());
	Shader* engineShader = engine.getShader();
	Shader* textShader = new Shader("Engine/Shader/textOverlayShaders/text.vs", "Engine/Shader/textOverlayShaders/text.fs");
	Model* myModel = new Model("Engine/ModelSrc/cyborg/cyborg.obj", 0.5, vec3(-1.0f));
	DirLight light1 = DirLight();
	PointLight light2 = PointLight(vec3(1.0f, 1.0f, 1.0f));
	SpotLight light3 = SpotLight(vec3(1.0f, 1.0f, 1.0f), vec3(0.5f, 1.0f, 0.3f));
	Cube cube1 = Cube(1, vec3(0.0f));
	Cube cube2 = Cube(1, vec3(0.0f, 5.0f, 0.0f));
	cout << "--------------------------------------------" << endl;
	cout << "THE FLOORPLANE CLASS IS INEFFICIENT DO NOT USE" << endl;
	cout << "--------------------------------------------" << endl;
	//FloorPlane plane = FloorPlane(1);
	//Model crystal2 = Model("Engine/ModelSrc/cube/crystal1.3ds", 0.5, vec3(1.0f));
	

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	vec3 start = camUser->camPos + vec3(10, 0, 10);

	cout << "Initializing FreeType lib" << endl;
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		cout << "ERROR::FREETYPE: could not init freetype lib" << endl;
	}
	
	FT_Face face;
	if (FT_New_Face(ft, "Engine/fonts/arial.ttf", 0, &face)) {
		cout << "ERROR::FREETYPE: Failed to load font" << endl;
	}

	Mesh cubeMesh = cube1.getMesh();
	cubeMesh.SaveToFile("file1.txt");

	Mesh newMesh = loadMeshFromFile("file1.txt");

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	cout << "calculating typeface" << endl;
	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			cout << "ERROR::FREETYPE: Failed to load Glyph" << endl;
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture, ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(pair<GLchar, Character >(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);



	cout << "Done." << endl;
	while (!glfwWindowShouldClose(engine.getWindow())) {

		//per-frame time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		vec3 start = camUser->camPos;
		//processing input and beginning the render
		engine.setShaderMains(camUser, engineShader);
		processInput(engine.getWindow(), camUser);
		engine.Update();
		engine.BeginRender(worldColor);

		engineShader->use();

		light2.setPosition(vec3(cos(currentFrame) / 2, 0.0f, sin(currentFrame) / 2));

		light3.setPosition(camUser->camPos);
		light3.setDirection(camUser->camFront);
		engineShader->setFloat("material.shininess",512.0f);


		light1.Draw(engineShader);
		light2.Draw(engineShader);
		light3.DrawLight(engineShader);

		textShader->use();
		//RenderText(*textShader, "tuna", 10, 10, 1, vec3(0.5, 1.0, 0.0));
		
		engineShader->use();
		mat4 model = mat4(1.0f);
		engineShader->setMat4("model", model);
		newMesh.Draw(*engineShader);
		//ending render
		engine.EndRender();
	}
	floors.clear();
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window, Camera* cam) {
	if (keyboardMode == CAMERA_TRANSLATE) {
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && alreadyPressed==false) {
			if (wireframe == false) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				wireframe = true;
				alreadyPressed = true;
				cout << "Wireframe enabled" << endl;
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				wireframe = false;
				alreadyPressed = true;
				cout << "wireframe disabled" << endl;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
			alreadyPressed = false;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cam->camPos += camSpeed * cam->camFront;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cam->camPos -= camSpeed * cam->camFront;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cam->camPos -= normalize(cross(cam->camFront, cam->camUp)) *camSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cam->camPos += normalize(cross(cam->camFront, cam->camUp)) *camSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			camSpeed = 0.15;
		}
		else {
			camSpeed = 0.05;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			if (worldColor.x < 1) {
				worldColor += vec3(0.01f, 0.01f, 0.01f);
			}
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			if (worldColor.x > 0.05) {
				worldColor -= vec3(0.01f, 0.01f, 0.01f);
			}
		}
		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && tabPressed==false) {
			tabPressed = true;
			cout << "Mouse Mode: Cursor Mode" << endl;
			cout << "Keyboard Mode: text input" << endl;
			keyboardMode = TEXT_INPUT;
			mouseMode = CURSOR_SHOW;
		}
		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE && tabPressed == true) {
			tabPressed = false;
		}
	}
	if (keyboardMode == TEXT_INPUT) {
		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && tabPressed==false) {
			tabPressed = true;
			cout << "Mouse Mode: Camera Movement" << endl;
			cout << "Keyboard Mode: Camera Movement" << endl;
			keyboardMode = CAMERA_TRANSLATE;
			mouseMode = CAMERA_MOVE;
		}
		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE && tabPressed == true) {
			tabPressed = false;
		}
	}
}



void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	if (scrollMode == ZOOM) {
		if ((camUser->zoom > radians(140.0f))) {
			camUser->zoom = radians(140.0f);
		}
		if ((camUser->zoom < radians(50.0f))) {
			camUser->zoom = radians(50.0f);
		}
		camUser->zoom -= radians((float)yOffset) * 2;
	}
}

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (mouseMode == CAMERA_MOVE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (firstMouse)
		{
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
		}

		float xoffset = xPos - lastX;
		float yoffset = lastY - yPos; // reversed since y-coordinates go from bottom to top

		lastX = xPos;
		lastY = yPos;

		camUser->processMouseMovement(xoffset, yoffset);
	}
	if (mouseMode == CURSOR_SHOW) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

Mesh loadMeshFromFile(const char* fileName) {
	cout << "loading " << fileName << endl;
	ifstream inputFile;
	inputFile.open(fileName);
	char label;
	char data[512];
	Vertex v;
	Texture t;
	vector<Vertex> vertexs;
	vector<unsigned int> indexs;
	vector<Texture> texs;
	vector<int> index;
	int vertexDataNum = 1;
	string value;
	label = inputFile.get();
	while (!inputFile.eof()) {
		if (label == 'v') {
			inputFile.getline(data, 512);
			for (int i = 0; i < sizeof(data); i++) {
				if (data[i] == '{') {}
				else {
					if (data[i] == ',' || data[i] == '}') {
						switch (vertexDataNum) {
						case 1: v.Position.x = stof(value);
						case 2: v.Position.y = stof(value);
						case 3: v.Position.z = stof(value);
						case 4: v.Normal.x = stof(value);
						case 5: v.Normal.y = stof(value);
						case 6: v.Normal.z = stof(value);
						case 7: v.Bitangent.x = stof(value);
						case 8: v.Bitangent.y = stof(value);
						case 9: v.Bitangent.z = stof(value);
						case 10: v.Tangent.x = stof(value);
						case 11: v.Tangent.y = stof(value);
						case 12: v.Tangent.z = stof(value);
						case 13: v.TexCoords.x = stof(value);
						case 14: v.TexCoords.y = stof(value);
						}
						vertexDataNum++;
						value = "";
						if (data[i] == '}') {
							vertexs.push_back(v);
							break;
						}
					}
					else {
						value += data[i];
					}
				}
			}
			label = inputFile.get();
		}
		if (label == 'i') {
			int indexFileNum = 1;
			inputFile.getline(data, 512);
			for (int i = 0; i < sizeof(data); i++) {
				if (data[i] == '{') {}
				else {
					if (data[i] == ',' || data[i] == '}') {
						switch (indexFileNum) {
						case 1: indexs.push_back(stoi(value));
						case 2: indexs.push_back(stoi(value));
						case 3: indexs.push_back(stoi(value));
						}
						indexFileNum++;
						value = "";
						if (data[i] == '}') {
							break;
						}
					}
					else {
						value += data[i];
					}
				}
			}
			label = inputFile.get();
		}
		if (label == 't') {
			int textureFileNum = 1;
			inputFile.getline(data, 512);
			for (int i = 0; i < sizeof(data); i++) {
				if (data[i] == '{') {
				}
				else {
					if (data[i] == ',' || data[i] == '}') {
						switch (textureFileNum) {
						case 1: t.id = stoi(value);
						case 2: t.path = value;
						case 3: t.type = value;
						}
						textureFileNum++;
						value = "";
						if (data[i] == '}') {
							texs.push_back(t);
							break;
						}
					}
					else {
						value += data[i];
					}
				}
			}
			label = inputFile.get();
		}
	}
	cout << "Done." << endl;
	return Mesh(vertexs, indexs, texs);
}