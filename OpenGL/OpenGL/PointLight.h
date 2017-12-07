#pragma once
#include "Light.h"
class PointLight : public Light
{
private:
	const vec3 COLOR = vec3(1.0f), POSITION = vec3(0.0f, 0.0f, 0.0f);
	const float AMBIENT = 0.05f, DIFFUSE = 0.8f, SPECULAR = 1.0f, CONSTANT = 1.0f, LINEAR = 0.09f, QUADRATIC = 0.032f;
public:
	/* Create pointlight */
	PointLight();
	/* Create pointlight */
	PointLight(const vec3 & color, const vec3 & position);
	/* Create pointlight */
	PointLight(const vec3 & color, const vec3 & position, const float & ambient, const float & diffuse, const float & specular);
	/* Create pointlight */
	PointLight(const vec3 & color, const vec3 & position, const float & ambient, const float & diffuse, const float & specular, const float & constant, const float & linear, const float & quadratic);
	/* De-constructor */
	~PointLight();
};