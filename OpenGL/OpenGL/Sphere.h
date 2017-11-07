#pragma once

#include "Mesh.h"
#include "Diamond.h"

/* https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere */

class Sphere : public Mesh
{
private:
	const float WIDTH = 1.0f;
	const unsigned int QUALITY = 4;
public:
	Sphere();
	Sphere(const float width, const unsigned int quality);
	~Sphere();
	void createSphere(const float width, const unsigned int quality);
	void breakup(const unsigned int times);
	vec3 midpoint(const vec3 & a, const vec3 & b);
	vec2 midpoint(const vec2 & a, const vec2 & b);
};