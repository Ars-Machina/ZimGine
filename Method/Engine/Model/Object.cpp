#include "Object.h"
#include "../ExternVar.h"

Object::Object() {
	rotation = vec3(0.0f);
	velocity = vec3(0.0f);
	position = vec3(0.0f);
	size = 1;
}
Object::Object(int objectType) {
	rotation = vec3(0.0f);
	velocity = vec3(0.0f);
	position = vec3(0.0f);
	size = 1;
	if (objectType == BZ_CUBE) {
		objectModel = Model("Engine/ModelSrc/cube/cube.3ds");
	}
	else {
		cout << "Object ID of " << objectType << " doesnt exist" << endl;
		logFile << "Object ID of " << objectType << " doesnt exist" << endl;
	}
}
Object::Object(const char* filename) {
	rotation = vec3(0.0f);
	velocity = vec3(0.0f);
	position = vec3(0.0f);
	size = 1;
	objectModel = Model(filename);
}
void Object::Draw(Shader &shader) {
	shader.use();
	mat4 model = mat4(1.0f);
	model = translate(model, position);
	model = scale(model, vec3(size));
	shader.setMat4("model", model);
	objectModel.Draw(shader);
}
void Object::setPos(vec3 newPos) {
	position = newPos;
}
void Object::setVelocity(vec3 newVelocity) {
	velocity = newVelocity;
}
void Object::setRotation(vec3 newRotation) {
	rotation = newRotation;
}
void Object::setSize(int newSize) {
	size = newSize;
}