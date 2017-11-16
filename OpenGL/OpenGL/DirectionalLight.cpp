#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	this->type = DIRECTIONAL;
	this->id = directional_light_counter++;
	this->color = COLOR;
	this->direction = DIRECTION;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
}

DirectionalLight::DirectionalLight(const vec3 & color, const vec3 & direction)
{
	this->type = DIRECTIONAL;
	this->id = directional_light_counter++;
	this->color = color;
	this->direction = direction;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
}

DirectionalLight::DirectionalLight(const vec3 & color, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular)
{
	this->type = DIRECTIONAL;
	this->id = directional_light_counter++;
	this->color = color;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

DirectionalLight::~DirectionalLight()
{
}
