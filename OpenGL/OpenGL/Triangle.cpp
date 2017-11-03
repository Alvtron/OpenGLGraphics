#include "Triangle.h"

unsigned int Triangle::num_triangles = 0;

/* Create a Triangle object that stores vertex data: vertices, normals, colors and textures. Call createVertexData(...) to add vertex data. */
Triangle::Triangle() : Mesh()
{
	num_triangles++;
}

/* Create a Triangle object that stores vertex data: vertices, normals, colors and textures. Call createVertexData(...) to add vertex data. */
Triangle::Triangle(float base) : Mesh()
{
	vertices = createTriangle(base, getHeight(base, base));
	Mesh::createVertexData(vertices, normals, colors, textures);
	num_triangles++;
}

/* Create a Triangle object that stores vertex data: vertices, normals, colors and textures. Call createVertexData(...) to add vertex data. */
Triangle::Triangle(float base, float height) : Mesh()
{
	vertices = createTriangle(base, height);
	Mesh::createVertexData(vertices, normals, colors, textures);
	num_triangles++;
}

/* De-constructor */
Triangle::~Triangle()
{
	num_triangles--;
}

/* Create a triangle. Returns it's vertices */
std::vector<vec3> Triangle::createTriangle(float base, float height)
{
	return {
		vec3(-(base / 2.0f), -(height / 2.0f), 0.0f),
		vec3((base / 2.0f), -(height / 2.0f), 0.0f),
		vec3(0.0f, (height / 2), 0.0f)
	};
}

/* Create a triangle. Returns it's vertices */
std::vector<vec3> Triangle::createTriangle(float side)
{
	return {
		vec3(-(side / 2.0f), -(side / 2.0f), 0.0f),
		vec3((side / 2.0f), -(side / 2.0f), 0.0f),
		vec3(0.0f, (side / 2), 0.0f)
	};
}

std::vector<vec3> Triangle::getVertices()
{
	return vertices;
}

std::vector<vec3> Triangle::getNormals()
{
	return normals;
}

std::vector<vec3> Triangle::getColors()
{
	return colors;
}

std::vector<vec2> Triangle::getTextures()
{
	return textures;
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

/* Return number of triangles of rectangle */
int Triangle::getNumTriangles()
{
	return num_triangles;
}
