#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <iostream>
#include "shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <map>

class Text {

struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
	};

private: 
	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;
	
public:
	void initFonts(std::string fontPath, int WINDOW_HEIGHT, int WINDOW_WIDTH);
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	Shader textShader;

};