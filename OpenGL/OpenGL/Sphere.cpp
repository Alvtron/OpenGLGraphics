#include "Sphere.h"

Sphere::Sphere()
{
	createSphere(WIDTH, QUALITY);
}

Sphere::Sphere(const float width, const unsigned int quality)
{
	createSphere(width, quality);
}

Sphere::~Sphere()
{
}

void Sphere::createSphere(const float width, const unsigned int quality) {
	float radius = width / 2.0f;

	Diamond diamond = Diamond(width);
	
	vertices = diamond.vertices;
	uvs = diamond.uvs;
	subdivide(quality);

	for (int i = 0; i < vertices.size(); i++)
		vertices.at(i) = vec3::scale(vec3::normalize(vertices.at(i)), width);
}