#pragma once
#include "Light.h"

class SpotLight : public Light
{
private:
	const vec3 COLOR = vec3(1.0f), POSITION = vec3(0.0f, 0.0f, 0.0f), DIRECTION = vec3(0.0f, -1.0f, 0.0f);
	const float AMBIENT = 0.05f, DIFFUSE = 0.8f, SPECULAR = 1.0f, CONSTANT = 1.0f, LINEAR = 0.09f, QUADRATIC = 0.032f, CUTOFF = 12.5f, OUTERCUTOFF = 15.0f;
public:
	/* Create spotlight. Use default parameters. */
	SpotLight();
	/* Create spotlight. */
	SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction);
	/* Create spotlight. */
	SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular);
	/* Create spotlight. */
	SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic);
	/* Create spotlight. */
	SpotLight(const vec3 & color, const vec3 & position, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic, const float & cutOff, const float & outerCutOff);
	/* Create spotlight that is attached to the camera */
	SpotLight(Camera * camera, const vec3 & color);
	/* Create spotlight that is attached to the camera */
	SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular);
	/* Create spotlight that is attached to the camera */
	SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic);
	/* Create spotlight that is attached to the camera */
	SpotLight(Camera * camera, const vec3 & color, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic, const float & cutOff, const float & outerCutOff);
	/* Deconstructor */
	~SpotLight();
};