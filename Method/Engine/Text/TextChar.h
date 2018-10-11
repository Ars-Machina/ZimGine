#ifndef TEXTCHAR_H
#define TEXTCHAR_H

#include "../include.h"
#include <map>

void RenderText(Shader &shader, string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
void setupText();

struct Character {
	GLuint TextureID;
	ivec2 Size;
	ivec2 Bearing;
	GLuint Advance;
};

static map<GLchar, Character> Characters;

#endif