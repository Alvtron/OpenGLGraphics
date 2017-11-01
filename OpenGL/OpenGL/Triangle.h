#pragma once
#include "Mesh.h"
class Triangle : public Mesh
{
public:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	static unsigned int num_triangles;
	
	std::vector<glm::vec3> vertices = {
		glm::vec3(-(WIDTH / 2.0f), -(HEIGHT / 2.0f), 0.0f),
		glm::vec3(WIDTH / 2.0f, -(HEIGHT / 2.0f), 0.0f),
		glm::vec3(+0, HEIGHT / 2, 0.0f)
	};
	std::vector<glm::vec3> normals = {
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f)
	};
	std::vector<glm::vec3> colors = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};
	std::vector<glm::vec2> textures = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f)
	};
public:
	Triangle();
	Triangle(float width);
	Triangle(float width, float height);
	~Triangle();
	std::vector<glm::vec3> createTriangle(float base, float height);
	std::vector<glm::vec3> createTriangle(float side);
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getColors();
	std::vector<glm::vec2> getTextures();
	float getHeight(float ground, float side);
	float getAreal(float base, float height);
	int getNumTriangles();
};

