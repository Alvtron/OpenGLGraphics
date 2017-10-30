#pragma once

#include "Mesh.h"
#include "Diamond.h"

/* https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere */

class Sphere : public Mesh
{
private:
	static unsigned int num_spheres;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec2> textures;
public:
	Sphere();
	Sphere(float size, unsigned int quality);
	~Sphere();
	void breakup(unsigned int times);
	glm::vec3 midpoint(glm::vec3 a, glm::vec3 b);
	glm::vec2 midpoint(glm::vec2 a, glm::vec2 b);
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getColors();
	std::vector<glm::vec2> getTextures();
};