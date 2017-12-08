#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <vector>

class Texture
{
private:
public:
	static unsigned int active_textures;
	unsigned int id, index;
	int width, height, depth;

	/* Default constructor */
	Texture();
	/* Construct texture with image. Specify filepath */
	Texture(char const * path);
	/* De-constructor */
	~Texture();
};

void activateTexture(Texture * t);

/*
Author: Rikard Olajos. Texture from noise file generated Rikard Olajos
https://github.com/rikardolajos/clouds/blob/master/src/texture.cpp
https://github.com/rikardolajos/noisegen/tree/master/NoiseGen
*/
bool createTexture3DFromEX5(Texture * t, const char * file_path);