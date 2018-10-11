#ifndef TEXTCHAR_H
#define TEXTCHAR_H

#include "../include.h"
#include <map>

void RenderText(Shader &shader, string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);

struct Character {
	GLuint TextureID;
	ivec2 Size;
	ivec2 Bearing;
	GLuint Advance;
};

map<GLchar, Character> Characters;

void RenderText(Shader &shader, string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color) {
	string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = Characters[*c];

		GLfloat xPos = x + ch.Bearing.x * scale;
		GLfloat yPos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;

		GLfloat vertices[6][4] = {
			{xPos, yPos + h, 0.0, 0.0},
			{xPos, yPos, 0.0,1.0},
			{xPos + w, yPos, 1.0,1.0},

			{xPos, yPos + h, 0.0,0.0},
			{xPos + w, yPos, 1.0,1.0},
			{xPos + w, yPos + h, 1.0,0.0}
		};
	}
}


#endif
