#pragma once
#include "Mesh.h"

class Rect : public Mesh
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	static unsigned int num_rectangles;
	
	std::vector<vec3> vertices = {
		vec3(-(WIDTH / 2.0f), -(HEIGHT / 2.0f), 0.0f),
		vec3(+(WIDTH / 2.0f), -(HEIGHT / 2.0f), 0.0f),
		vec3(+(WIDTH / 2.0f), +(HEIGHT / 2.0f), 0.0f),
		vec3(-(WIDTH / 2.0f), +(HEIGHT / 2.0f), 0.0f)
	};
	std::vector<vec3> normals = {
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f)
	};
	std::vector<vec3> colors = {
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f)
	};
	std::vector<vec2> textures = {
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f)
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};
public:
	Rect();
	Rect(float width, float height);
	Rect(float width, float height, vec3 position);
	~Rect();
	std::vector<vec3> createRectangle(float width, float height, vec3 position);
	std::vector<vec3> getVertices();
	std::vector<vec3> getNormals();
	std::vector<vec3> getColors();
	std::vector<vec2> getTextures();
	std::vector<unsigned int> getIndices();
	float getWidth();
	float getHeight();
	float getArea();
	int getNumRectangles();
};