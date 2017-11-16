#pragma once
#include "maths.h"
#include "Shader.h"
#include "Camera.h"
#include "glm.hpp"

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
	Light();
	~Light();
	bool is(Type type);
	void enable();
	void disable();
	bool isEnabled();
	bool drawLight(const Shader * shader);
	Type getType();
	bool operator ==(const Light& right) const;
	static unsigned int numDirectionalLights();
	static unsigned int numPointLights();
	static unsigned int numSpotLights();
};