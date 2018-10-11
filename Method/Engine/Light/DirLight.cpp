#include "DirLight.h"

DirLight::DirLight() {
	setup();
}

void DirLight::setup() {
	float vertices[] = {
		0.5f,-0.5f,0.0f,
		-0.5f,0.5f,0.0f,
		0.0f,0.5f,0.0f
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void DirLight::Draw(Shader* shader) {
	shader->setVec3("dirLight.direction", vec3(1.0f, 1.0f, 1.0f));
	shader->setVec3("dirLight.ambient", vec3(0.2f, 0.2f, 0.2f));
	shader->setVec3("dirLight.diffuse", vec3(0.5f, 0.5f, 0.5f));
	shader->setVec3("dirLight.specular", vec3(1.0f, 0.5f, 0.32f));
}