#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
private:
	const vec3 COLOR = vec3(1.0f), DIRECTION = vec3(0.0f, -1.0f, 0.0f);
	const float AMBIENT = 0.05f, DIFFUSE = 0.2f, SPECULAR = 0.2f;
public:
	/* Create Directional Light */
	DirectionalLight();
	/* Create Directional Light */
	DirectionalLight(const vec3 & color, const vec3 & direction);
	/* Create Directional Light */
	DirectionalLight(const vec3 & color, const vec3 & direction, const float & ambient, const float & diffuse, const float & specular);
	/* De-constructor */
	~DirectionalLight();
};

