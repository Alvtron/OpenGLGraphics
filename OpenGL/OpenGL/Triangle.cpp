#include "Triangle.h"

/* Create a Triangle object that stores vertex data */
Triangle::Triangle()
{
	createTriangle(WIDTH, getHeight(WIDTH, WIDTH));
}

/* Create a Triangle object that stores vertex data */
Triangle::Triangle(float base)
{
	createTriangle(base, getHeight(base, base));
}

/* Create a Triangle object that stores vertex data */
Triangle::Triangle(float base, float height)
{
	createTriangle(base, height);
}

/* De-constructor */
Triangle::~Triangle()
{
}

/* Create a triangle. */
void Triangle::createTriangle(float base, float height)
{
	vertices = {
		vec3(-(base / 2.0f), -(height / 2.0f), 0.0f),
		vec3((base / 2.0f), -(height / 2.0f), 0.0f),
		vec3(0.0f, (height / 2), 0.0f)
	};
	normals = {
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f),
		vec3(0.0f, 0.0f, -1.0f)
	};
	uvs = {
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f)
	};
	createColors();
	calculateTangents();
}

/* Create a triangle. */
void Triangle::createTriangle(float side)
{
	createTriangle(side, getHeight(side, side));
}

/* Return height of triangle */
float Triangle::getHeight(float base, float side)
{
	return sqrt(pow(side, 2) - pow((base / 2), 2));
}

/* Return area of triangle */
float Triangle::getAreal(float base, float height)
{
	return (height * base) / 2.0f;
}