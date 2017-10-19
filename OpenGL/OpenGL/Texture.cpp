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

// Texture shading configuration
void Texture::SetShaderSampler(Shader * shader) {
	shader->use();
	shader->setInt("material.diffuse", 0);
	shader->setInt("material.specular", 1);
	shader->setInt("material.normal", 2);
	shader->setInt("material.displacement", 3);
	shader->setInt("material.ao", 4);
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

bool Texture::addTexture(const std::string path, const TEXTURE_TYPE type)
{
	if (type == TXT_DIFFUSE)
	{
		return addDiffuse(path.c_str());
	}
	else if (type == TXT_SPECULAR)
	{
		return addSpecular(path.c_str());
	}
	else if (type == TXT_NORMAL)
	{
		return addNormal(path.c_str());
	}
	else if (type == TXT_DISPLACEMENT)
	{
		return addDisplacement(path.c_str());
	}
	else if (type == TXT_AO)
	{
		return addAO(path.c_str());
	}
	else return false;
}

bool Texture::addDiffuse(const std::string path)
{
	diffuseBound = bindTexture(path.c_str(), diffuse_id);
	return diffuseBound;		
}

bool Texture::addSpecular(const std::string path)
{
	specularBound = bindTexture(path.c_str(), specular_id);
	return specularBound;
}

bool Texture::addNormal(const std::string path)
{
	normalBound = bindTexture(path.c_str(), normal_id);
	return normalBound;
}

bool Texture::addDisplacement(const std::string path)
{
	displacementBound = bindTexture(path.c_str(), displacement_id);
	return displacementBound;
}

bool Texture::addAO(const std::string path)
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

bool Texture::hasDisplacement()
{
	return displacementBound;
}

bool Texture::hasAO()
{
	return AOBound;
}

unsigned int Texture::getDiffuse()
{
	return diffuse_id;
}

unsigned int Texture::getSpecular()
{
	return specular_id;
}

unsigned int Texture::getNormal()
{
	return normal_id;
}

unsigned int Texture::getDisplacement()
{
	return displacement_id;
}

unsigned int Texture::getAO() {
	return ao_id;
}

unsigned int Texture::getNumTextures()
{
	return num_textures;
}