#pragma once
#include "maths.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Entity
{
public:
	int mass = 0;
	bool isSolid = true;
	vec3 position;
	vec3 hitbox;
	vec3 scale;
	bool exist = true;

	Entity() {};

	Entity(vec3 position, vec3 hitbox, vec3 scale, bool isSoild)
	{
		this->position = position;
		this->hitbox = hitbox;
		this->scale = scale;
		this->isSolid = isSoild;
	}

	Entity(vec3 position, vec3 hitbox, vec3 scale, bool isSoild, bool exist)
	{
		this->position = position;
		this->hitbox = hitbox;
		this->scale = scale;
		this->isSolid = isSoild;
		this->exist = exist;
	}
};