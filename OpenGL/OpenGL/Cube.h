#pragma once
#include "Vertex.h"

class Cube : public Vertex
{
private:
	const unsigned short SIZE = 24;
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	/* Create a cube */
	void createCube(const float width, const float height);
public:
	/* Create a Cube object with default sizes. */
	Cube();
	/* Create a Cube object with width. */
	Cube(float width);
	/* Create a Cube object with width and height. */
	Cube(float width, float height);
	/* De-constructor */
	~Cube();
};