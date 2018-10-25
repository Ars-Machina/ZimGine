#include "PointLight.h"

PointLight::PointLight(vec3 pos, int id) {
	position = pos;
	this->id = id;
	setup();
}

void PointLight::setup() {
	float vertices[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void PointLight::Draw(Shader* shader) {
	string idStr = to_string(id);
	string plBase = string("pointLight[");
	string plEnd = string("].");
	string plPos = string("position");
	string plAmb = string("ambient");
	string plDif = string("diffuse");
	string plSpec = string("specular");
	string plConst = string("constant");
	string plLin = string("linear");
	string plQuad = string("quadratic");

	shader->use();
	shader->setVec3((plBase + idStr + plEnd + plPos), position);
	shader->setVec3((plBase + idStr + plEnd + plAmb), vec3(0.2f, 0.2f, 0.2f));
	shader->setVec3((plBase + idStr + plEnd + plDif), vec3(0.5f, 0.5f, 0.5f));
	shader->setVec3((plBase + idStr + plEnd + plSpec), vec3(1.0f, 0.5f, 0.31f));
	shader->setFloat((plBase + idStr + plEnd + plConst), 1.0f);
	shader->setFloat((plBase + idStr + plEnd + plLin), 0.09f);
	shader->setFloat((plBase + idStr + plEnd + plQuad), 0.032f);
	
	
}

void PointLight::Draw2(Shader* shader, mat4 view, mat4 projection, mat4 model) {
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

unsigned int PointLight::getVAO() {
	return VAO;
}

void PointLight::setPosition(vec3 pos) {
	position = pos;
}