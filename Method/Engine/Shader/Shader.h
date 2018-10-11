#ifndef SHADER_H
#define SHADER_H


#include "../include.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string>

class Shader {
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader();
	void use();
	void setBool(const std::string&, bool);
	void setInt(const std::string&, int);
	void setFloat(const std::string&, float);
	void setVec3(const std::string&, glm::vec3);
	void setMat4(const std::string&, glm::mat4);
};
#endif