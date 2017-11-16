#pragma once
#include "Vertex.h"

class Cube : public Vertex
{
private:
	const unsigned short SIZE = 24;
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
public:
	Cube();
	Cube(float width);
	Cube(float width, float height);
	~Cube();
	void createCube(const float width, const float height);
};