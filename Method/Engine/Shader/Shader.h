#ifndef SHADER_H
#define SHADER_H


#include <GL/glew.h>
#define GLEW_STATIC
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using namespace glm;

using namespace std;

class Shader {
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader();
	void use();
	void setBool(const string &name, bool value)const;
	void setInt(const string &name, int value)const;
	void setFloat(const string &name, float value)const;
	void setVec3(const string &name, vec3 value)const;
	void setMat4(const string &name, mat4 value)const;
};
#endif