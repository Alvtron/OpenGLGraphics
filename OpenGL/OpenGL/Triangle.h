#pragma once
#include "Mesh.h"
class Triangle : public Mesh
{
public:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	static unsigned int num_triangles;
	
	std::vector<vec3> vertices = {
		vec3(-(WIDTH / 2.0f), -(HEIGHT / 2.0f), 0.0f),
		vec3(WIDTH / 2.0f, -(HEIGHT / 2.0f), 0.0f),
		vec3(+0, HEIGHT / 2, 0.0f)
	};
	std::vector<vec3> normals = {
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f)
	};
	std::vector<vec3> colors = {
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f)
	};
	std::vector<vec2> textures = {
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f)
	};
public:
	Triangle();
	Triangle(float width);
	Triangle(float width, float height);
	~Triangle();
	std::vector<vec3> createTriangle(float base, float height);
	std::vector<vec3> createTriangle(float side);
	std::vector<vec3> getVertices();
	std::vector<vec3> getNormals();
	std::vector<vec3> getColors();
	std::vector<vec2> getTextures();
	float getHeight(float ground, float side);
	float getAreal(float base, float height);
	int getNumTriangles();
};

