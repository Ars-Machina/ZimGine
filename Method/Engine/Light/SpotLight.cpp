#include "SpotLight.h"

SpotLight::SpotLight(vec3 pos, vec3 dir) {
	direction = dir;
	position = pos;
	setup();
}

void SpotLight::setup() {
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

void SpotLight::DrawLight(Shader* shader) {
	shader->use();
	shader->setVec3("spotLight.position", position);
	shader->setVec3("spotLight.direction", direction);
	shader->setFloat("spotLight.cutOff", cos(radians(12.5f)));
	shader->setFloat("spotLight.outerCutOff", cos(radians(17.5f)));
	shader->setFloat("spotLight.constant", 1.0f);
	shader->setFloat("spotLight.linear", 0.09f);
	shader->setFloat("spotLight.quadratic", 0.032f);
	shader->setVec3("spotLight.ambient", vec3(0.2f, 0.2f, 0.2f));
	shader->setVec3("spotLight.diffuse", vec3(0.5f, 0.5f, 0.5f));
	shader->setVec3("spotLight.specular", vec3(1.0f, 0.5f, 0.31f));
}

void SpotLight::DrawObject(Shader* shader, mat4 view, mat4 projection, mat4 model) {
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void SpotLight::setDirection(vec3 dir) {
	direction = dir;
}

void SpotLight::setPosition(vec3 pos) {
	position = pos;
}