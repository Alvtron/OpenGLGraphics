#pragma once
#include "Mesh.h"

class Rect : public Mesh
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	
public:
	Rect();
	Rect(float width, float height);
	Rect(float width, float height, vec3 position);
	~Rect();
	void createRectangle(float width, float height, vec3 position);
};