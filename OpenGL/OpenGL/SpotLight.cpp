#include "SpotLight.h"

SpotLight::SpotLight()
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = COLOR;
	this->position = POSITION;
	this->direction = DIRECTION;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction)
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular)
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic)
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic, const float & cutOff, const float & outerCutOff)
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->position = position;
	this->direction = direction;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}

SpotLight::SpotLight(Camera * camera, const vec3 & color)
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->camera = camera;
	this->ambient = AMBIENT;
	this->diffuse = DIFFUSE;
	this->specular = SPECULAR;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular)
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->camera = camera;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = CONSTANT;
	this->linear = LINEAR;
	this->quadratic = QUADRATIC;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic)
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->camera = camera;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = CUTOFF;
	this->outerCutOff = OUTERCUTOFF;
}

SpotLight::SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic, const float & cutOff, const float & outerCutOff)
{
	this->type = SPOT;
	this->id = spot_light_counter++;
	this->color = color;
	this->camera = camera;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}

SpotLight::~SpotLight()
{
}
