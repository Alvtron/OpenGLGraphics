#pragma once
#include "maths.h"
#include "Shader.h"
#include "Camera.h"
#include "glm.hpp"
#include <string>

#define DISABLED vec3(0.0f)

class Light
{
private:
	bool enabled = true;
public:
const enum Type : short {
		UNSET = 0,
		DIRECTIONAL = 1,
		POINT = 2,
		SPOT = 3
	};
protected:
	Type type;
	unsigned int id;
	Camera * camera = nullptr;
	static unsigned int directional_light_counter, point_light_counter, spot_light_counter;
public:
	vec3 color, position, direction;
	float ambient = -1.f, diffuse = -1.f, specular = -1.f, constant = -1.f, linear = -1.f, quadratic = -1.f, cutOff = -1.f, outerCutOff = -1.f;
	/* Constructor */
	Light();
	/* De-constructor */
	~Light();
	/* Check if light type is equal to specified light type */
	bool is(Type type);
	/* Enable light (will be drawn, on by default) */
	void enable();
	/* Disable light (will not be drawn) */
	void disable();
	/* Check if light is ON/enabled. */
	bool isEnabled();
	/* Draw light with shader (light shader) */
	bool drawLight(const Shader * shader);
	/* Get light type */
	Type getType();
	bool operator ==(const Light& right) const;
	/* Get number of Directional lights */
	static unsigned int numDirectionalLights();
	/* Get number of Point lights */
	static unsigned int numPointLights();
	/* Get number of Spot lights */
	static unsigned int numSpotLights();
};