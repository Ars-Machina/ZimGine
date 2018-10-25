#ifndef TEXTCHAR_H
#define TEXTCHAR_H

#include "../include.h"
#include "../Shader/Shader.h"
#include <map>

void RenderText(Shader &shader, string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
void setupText();

namespace textVAO {
	extern GLuint tVAO, tVBO;
}

struct Character {
	GLuint TextureID;
	ivec2 Size;
	ivec2 Bearing;
	GLuint Advance;
};

static map<GLchar, Character> Characters;

#endif