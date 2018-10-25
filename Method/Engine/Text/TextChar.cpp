#include "TextChar.h"
using namespace textVAO;


void RenderText(Shader &shader, string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color) {
	shader.use();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	mat4 projection = ortho(0.0f, 1400.0f, 0.0f, 900.0f);
	shader.setMat4("projection", projection);
	shader.setVec3("textColor", color);	
	string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) {
		Character ch = Characters[*c];

		GLfloat xPos = x + ch.Bearing.x * scale;
		GLfloat yPos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;

		GLfloat vertices[6][4] = {
			{ xPos,     yPos + h,   0.0, 0.0 },
			{ xPos,     yPos,       0.0, 1.0 },
			{ xPos + w, yPos,       1.0, 1.0 },

			{ xPos,     yPos + h,   0.0, 0.0 },
			{ xPos + w, yPos,       1.0, 1.0 },
			{ xPos + w, yPos + h,   1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, tVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6)*scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void setupText() {
	cout << "Initializing FreeType lib" << endl;
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		cout << "ERROR::FREETYPE: could not init freetype lib" << endl;
	}

	cout << "Initializing typeFace" << endl;
	FT_Face face;
	if (FT_New_Face(ft, "Engine/fonts/arial.ttf", 0, &face)) {
		cout << "ERROR::FREETYPE: Failed to load font" << endl;
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			cout << "ERROR::FREETYPE: Failed to load Glyph" << endl;
			continue;
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture, ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		Characters.insert(pair<GLchar, Character >(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	glGenVertexArrays(1, &tVAO);
	glGenBuffers(1, &tVBO);

	glBindVertexArray(tVAO);
	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}