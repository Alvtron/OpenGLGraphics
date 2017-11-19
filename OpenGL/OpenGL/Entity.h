#pragma once
#include "maths.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Entity
{
public:
	int mass = 0;
	vec3 position;
	vec3 hitbox;
	vec3 scale;

	Entity() {};

	Entity(vec3 position, vec3 hitbox, vec3 scale)
	{
		this->position = position;
		this->hitbox = hitbox;
		this->scale = scale;
	}
};