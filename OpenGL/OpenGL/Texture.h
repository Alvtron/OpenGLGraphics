#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "Shader.h"
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
	enum TEXTURE_TYPE : const unsigned int {
		TXT_DIFFUSE = 0,
		TXT_SPECULAR = 1,
		TXT_NORMAL = 2,
		TXT_DISPLACEMENT = 3,
		TXT_AO = 4
	};
	Texture();
	Texture(char const * diffusePath);
	~Texture();
	bool addTexture(const std::string path, const TEXTURE_TYPE type);
	bool addDiffuse(const std::string path);
	bool addSpecular(const std::string path);
	bool addNormal(const std::string path);
	bool addDisplacement(const std::string path);
	bool addAO(const std::string path);
	const bool hasDiffuse();
	const bool hasSpecular();
	const bool hasNormal();
	const bool hasDisplacement();
	const bool hasAO();
	const unsigned int getDiffuse();
	const unsigned int getSpecular();
	const unsigned int getNormal();
	const unsigned int getDisplacement();
	const unsigned int getAO();
	const static unsigned int getNumTextures();
};