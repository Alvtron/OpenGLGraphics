#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "shader.h"
#include <iostream>
#include <string>

class Texture
{
private:
	static unsigned int num_textures;
	unsigned int diffuse_id, specular_id, normal_id, displacement_id, ao_id;
	bool diffuseBound = false, specularBound = false, normalBound = false, displacementBound = false, AOBound = false;
	bool bindTexture(char const * path, unsigned int & id);
public:
	enum TEXTURE_TYPE : unsigned int {
		TXT_DIFFUSE = 0,
		TXT_SPECULAR = 1,
		TXT_NORMAL = 2,
		TXT_DISPLACEMENT = 3,
		TXT_AO = 4
	};
	Texture();
	~Texture();
	bool addTexture(const std::string path, const TEXTURE_TYPE type);
	bool addDiffuse(const std::string path);
	bool addSpecular(const std::string path);
	bool addNormal(const std::string path);
	bool addDisplacement(const std::string path);
	bool addAO(const std::string path);
	bool hasDiffuse();
	bool hasSpecular();
	bool hasNormal();
	bool hasDisplacement();
	bool hasAO();
	unsigned int getDiffuse();
	unsigned int getSpecular();
	unsigned int getNormal();
	unsigned int getDisplacement();
	unsigned int getAO();
	static unsigned int getNumTextures();
};