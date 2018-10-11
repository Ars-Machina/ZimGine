#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "GL/glew.h"
#define GLEW_STATIC
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../../ModelSrc/cube/Cube.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

void DoCollisions(Cube cube1, Cube cube2) {
	if ((cube1.getPos().x - cube2.getPos().x < 1) && (cube1.getPos().y - cube2.getPos().y < 1) && (cube1.getPos().z - cube2.getPos().z < 1)) {
		cube1.setVelocity(vec3(0));
		cube2.setVelocity(vec3(0));
	}
}

void DoCollisions(vec3 position1, vec3 position2) {

}

#endif