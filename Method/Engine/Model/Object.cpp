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
	getBounds();
}
Object::Object(const char* filename) {
	rotation = vec3(0.0f);
	velocity = vec3(0.0f);
	position = vec3(0.0f);
	size = 1;
	objectModel = Model(filename);
	getBounds();
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
void Object::getBounds() {
	Mesh modelMesh = objectModel.getMesh();
	xMax = modelMesh.vertices[0].Position.x;
	xMin = modelMesh.vertices[0].Position.x;
	yMin = modelMesh.vertices[0].Position.y;
	yMax = modelMesh.vertices[0].Position.y;
	zMin = modelMesh.vertices[0].Position.z;
	zMax = modelMesh.vertices[0].Position.z;
	for (int i = 0; i < modelMesh.vertices.size(); i++) {
		vec3 v = modelMesh.vertices[i].Position;
		if (v.x > xMax) {
			xMax = v.x;
		}
		if (v.y > yMax) {
			yMax = v.y;
		}
		if (v.z > zMax) {
			zMax = v.z;
		}
		if (v.x < xMin) {
			xMin = v.x;
		}
		if (v.y < yMin) {
			yMin = v.y;
		}
		if (v.z < zMin) {
			zMin = v.z;
		}
	}
}

void Object::printObjectBounds() {
	cout << "X bounds" << xMin << ", " << xMax << endl;
	cout << "Y bounds" << yMin << ", " << yMax << endl;
	cout << "Z bounds" << zMin << ", " << zMax << endl;
}