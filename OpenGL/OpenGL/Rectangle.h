#pragma once
#include "Vertex.h"

class Rect : public Vertex
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	/* Creates the rectangle. */
	void createRectangle(float width, float height, vec3 position);
public:
	/* Create a Rectangle object. Uses default sizes. */
	Rect();
	/* Create a Rectangle object with width and height. */
	Rect(float width, float height);
	/* Create a Rectangle with width, height and position. */
	Rect(float width, float height, vec3 position);
	/* De-constructor */
	~Rect();
};