#include "PointLight.h"

PointLight::PointLight(vec3 pos) {
	position = pos;
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

	shader->use();
	shader->setVec3("pointLight.position", position);
	shader->setVec3("pointLignt.ambient", vec3(0.2f, 0.2f, 0.2f));
	shader->setVec3("pointLight.diffuse", vec3(0.5f, 0.5f, 0.5f));
	shader->setVec3("pointLight.specular", vec3(1.0f, 0.5f, 0.31f));
	shader->setFloat("pointLight.constant", 1.0f);
	shader->setFloat("pointLight.linear", 0.09f);
	shader->setFloat("pointLight.quadratic", 0.032f);
	
	
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