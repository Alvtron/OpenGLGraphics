#include "PointLight.h"

PointLight::PointLight()
{
	this->type = POINT;
	this->id = point_light_counter++;
	this->color = COLOR;
	this->position = POSITION;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
}

PointLight::PointLight(const vec3 & color, const vec3 & position)
{
	this->type = POINT;
	this->id = point_light_counter++;
	this->color = color;
	this->position = position;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
}

PointLight::PointLight(const vec3 & color, const vec3 & position, const float & ambient, const float & diffuse, const float & specular)
{
	this->type = POINT;
	this->id = point_light_counter++;
	this->color = color;
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
}

PointLight::PointLight(const vec3 & color, const vec3 & position, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic)
{
	this->type = POINT;
	this->id = point_light_counter++;
	this->color = color;
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

PointLight::~PointLight()
{
}