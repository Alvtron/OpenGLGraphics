#pragma once
#include "Mesh.h"

class Rect : public Mesh
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	static unsigned int num_rectangles;
	
	std::vector<glm::vec3> vertices = {
		glm::vec3(-(WIDTH / 2.0f), -(HEIGHT / 2.0f), 0.0f),
		glm::vec3(+(WIDTH / 2.0f), -(HEIGHT / 2.0f), 0.0f),
		glm::vec3(+(WIDTH / 2.0f), +(HEIGHT / 2.0f), 0.0f),
		glm::vec3(-(WIDTH / 2.0f), +(HEIGHT / 2.0f), 0.0f)
	};
	std::vector<glm::vec3> normals = {
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f)
	};
	std::vector<glm::vec3> colors = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};
	std::vector<glm::vec2> textures = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};
public:
	Rect();
	Rect(float width, float height);
	Rect(float width, float height, glm::vec3 position);
	~Rect();
	std::vector<glm::vec3> createRectangle(float width, float height, glm::vec3 position);
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getColors();
	std::vector<glm::vec2> getTextures();
	std::vector<unsigned int> getIndices();
	float getWidth();
	float getHeight();
	float getArea();
	int getNumRectangles();
};