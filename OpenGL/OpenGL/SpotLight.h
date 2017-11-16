#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
	const vec3 COLOR = vec3(1.0f), POSITION = vec3(0.0f, 0.0f, 0.0f), DIRECTION = vec3(0.0f, -1.0f, 0.0f);
	const float AMBIENT = 0.05f, DIFFUSE = 0.8f, SPECULAR = 1.0f, CONSTANT = 1.0f, LINEAR = 0.09f, QUADRATIC = 0.032f, CUTOFF = 12.5f, OUTERCUTOFF = 15.0f;
public:
	SpotLight();
	SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction);
	SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular);
	SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic);
	SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic, const float & cutOff, const float & outerCutOff);
	SpotLight(Camera * camera, const vec3 & color);
	SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular);
	SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic);
	SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic, const float & cutOff, const float & outerCutOff);
	~SpotLight();
};