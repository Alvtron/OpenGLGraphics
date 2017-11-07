#pragma once
#include "Mesh.h"
class Triangle : public Mesh
{
public:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
public:
	Triangle();
	Triangle(float width);
	Triangle(float width, float height);
	~Triangle();
	void createTriangle(float base, float height);
	void createTriangle(float side);
	float getHeight(float ground, float side);
	float getAreal(float base, float height);
};

