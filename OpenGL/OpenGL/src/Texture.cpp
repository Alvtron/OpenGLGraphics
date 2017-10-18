#include "Texture.h"

unsigned int Texture::num_textures = 0;

Texture::Texture()
{
	num_textures++;
}

Texture::~Texture()
{
	num_textures--;
}

bool Texture::bindTexture(char const * path, unsigned int &id)
{
	glGenTextures(1, &id);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
		return true;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
		return false;
	}
}

bool Texture::addTexture(std::string path, TEXTURE_TYPE type)
{
	if (type == TXT_DIFFUSE) return bindTexture(path.c_str(), diffuse_id);
	else if (type == TXT_SPECULAR) return bindTexture(path.c_str(), specular_id);
	else if (type == TXT_NORMAL) return bindTexture(path.c_str(), normal_id);
	else if (type == TXT_AO) return bindTexture(path.c_str(), ao_id);
	else return false;
}

bool Texture::addDiffuse(std::string path)
{
	diffuseBound = bindTexture(path.c_str(), diffuse_id);
	return diffuseBound;		
}

bool Texture::addSpecular(std::string path)
{
	specularBound = bindTexture(path.c_str(), specular_id);
	return specularBound;
}

bool Texture::addNormal(std::string path)
{
	normalBound = bindTexture(path.c_str(), normal_id);
	return normalBound;
}

bool Texture::addAO(std::string path)
{
	AOBound = bindTexture(path.c_str(), ao_id);
	return AOBound;
}

bool Texture::hasDiffuse() {
	return diffuseBound;
}

bool Texture::hasSpecular()
{
	return specularBound;
}

bool Texture::hasNormal()
{
	return normalBound;
}

bool Texture::hasAO()
{
	return AOBound;
}

unsigned int Texture::diffuse() {
	return diffuse_id;
}
unsigned int Texture::specular() {
	return specular_id;
}
unsigned int Texture::normal() {
	return normal_id;
}
unsigned int Texture::ao() {
	return ao_id;
}