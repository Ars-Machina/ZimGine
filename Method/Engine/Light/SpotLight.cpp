#include "SpotLight.h"

SpotLight::SpotLight(vec3 pos, vec3 dir, unsigned int newID) {
	direction = dir;
	position = pos;
	id = newID;
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
	string slId = to_string(id);
	string slBase = string("spotLight[");
	string slEnd = string("].");
	string slPos = string("position");
	string slDir = string("direction");
	string slCO = string("cutoff");
	string slOCO = string("outerCutOff");
	string slConst = string("constant");
	string slLin = string("linear");
	string slQuad = string("quadratic");
	string slAmb = string("ambient");
	string slDif = string("diffuse");
	string slSpec = string("specular");
	string slStart = slBase + slId + slEnd;
	shader->use();
	shader->setVec3((slStart+slPos), position);
	shader->setVec3((slStart+slDir), direction);
	shader->setFloat((slStart+slCO), cos(radians(12.5f)));
	shader->setFloat((slStart+slOCO), cos(radians(17.5f)));
	shader->setFloat((slStart+slConst), 1.0f);
	shader->setFloat((slStart+slLin), 0.09f);
	shader->setFloat((slStart+slQuad), 0.032f);
	shader->setVec3((slStart+slAmb), vec3(0.2f, 0.2f, 0.2f));
	shader->setVec3((slStart + slDif) , vec3(0.5f, 0.5f, 0.5f));
	shader->setVec3((slStart+slSpec), vec3(1.0f, 0.5f, 0.31f));
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