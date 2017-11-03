#pragma once

#include "Mesh.h"
#include "Diamond.h"

/* https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere */

class Sphere : public Mesh
{
private:
	static unsigned int num_spheres;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> colors;
	std::vector<vec2> textures;
public:
	Sphere();
	Sphere(float size, unsigned int quality);
	~Sphere();
	void breakup(unsigned int times);
	vec3 midpoint(vec3 a, vec3 b);
	vec2 midpoint(vec2 a, vec2 b);
	std::vector<vec3> getVertices();
	std::vector<vec3> getNormals();
	std::vector<vec3> getColors();
	std::vector<vec2> getTextures();
};