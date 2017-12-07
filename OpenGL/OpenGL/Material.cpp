#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::addDiffuse(const Texture & texture)
{
	this->diffuse = texture;
	this->diffuseBound = true;
}

void Material::addSpecular(const Texture & texture)
{
	this->specular = texture;
	this->specularBound = true;
}

void Material::addNormal(const Texture & texture)
{
	this->normal = texture;
	this->normalBound = true;
}

void Material::addDisplacement(const Texture & texture)
{
	this->displacement = texture;
	this->displacementBound = true;
}

void Material::addAmbientOcclusion(const Texture & texture)
{
	this->ambient_occlusion = texture;
	this->AOBound = true;
}

const bool Material::hasDiffuse() {
	return diffuseBound;
}

const bool Material::hasSpecular()
{
	return specularBound;
}

const bool Material::hasNormal()
{
	return normalBound;
}

const bool Material::hasDisplacement()
{
	return displacementBound;
}

const bool Material::hasAO()
{
	return AOBound;
}

void Material::bind()
{
	if (diffuseBound) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse.id);
	}
	if (specularBound) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specular.id);
	}
	if (normalBound) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, normal.id);
	}
	if (displacementBound) {
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, displacement.id);
	}
	if (AOBound) {
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, ambient_occlusion.id);
	}
}

void Material::unbind()
{
	if (diffuseBound) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (specularBound) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (normalBound) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (displacementBound) {
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	if (AOBound) {
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}