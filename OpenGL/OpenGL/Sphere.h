#pragma once

#include "Vertex.h"
#include "Diamond.h"

/* https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere */

class Sphere : public Vertex
{
private:
	const float WIDTH = 1.0f;
	const unsigned int QUALITY = 4;
public:
	Sphere();
	Sphere(const float width, const unsigned int quality);
	~Sphere();
	void createSphere(const float width, const unsigned int quality);
};