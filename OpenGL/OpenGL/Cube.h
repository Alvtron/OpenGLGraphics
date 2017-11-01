#pragma once
#include "Mesh.h"

class Cube : public Mesh
{
private:
	static unsigned int num_cubes;

	std::vector<glm::vec3> vertices = {
		// Front
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(+0.5f, -0.5f, -0.5f),	
		glm::vec3(+0.5f, +0.5f, -0.5f),	
		glm::vec3(-0.5f, +0.5f, -0.5f),	
		// Back
		glm::vec3(-0.5f, -0.5f, +0.5f),	
		glm::vec3(+0.5f, -0.5f, +0.5f),	
		glm::vec3(+0.5f, +0.5f, +0.5f),	
		glm::vec3(-0.5f, +0.5f, +0.5f),	
		// Left
		glm::vec3(-0.5f, -0.5f, +0.5f),	
		glm::vec3(-0.5f, -0.5f, -0.5f),	
		glm::vec3(-0.5f, +0.5f, -0.5f),	
		glm::vec3(-0.5f, +0.5f, +0.5f),	
		// Right
		glm::vec3(+0.5f, -0.5f, -0.5f),	
		glm::vec3(+0.5f, -0.5f, +0.5f),	
		glm::vec3(+0.5f, +0.5f, +0.5f),	
		glm::vec3(+0.5f, +0.5f, -0.5f),	
		// Bottom
		glm::vec3(-0.5f, -0.5f, -0.5f),	
		glm::vec3(+0.5f, -0.5f, -0.5f),	
		glm::vec3(+0.5f, -0.5f, +0.5f),	
		glm::vec3(-0.5f, -0.5f, +0.5f),	
		// Top
		glm::vec3(-0.5f, +0.5f, -0.5f),	
		glm::vec3(+0.5f, +0.5f, -0.5f),	
		glm::vec3(+0.5f, +0.5f, +0.5f),	
		glm::vec3(-0.5f, +0.5f, +0.5f)	
	};

	std::vector<glm::vec3> normals = {
		// Front
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		// Back
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		// Left
		glm::vec3(-1.0f, +0.0f, +0.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f),
		// Right
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		// Bottom
		glm::vec3(+0.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, -1.0f, +0.0f),
		glm::vec3(+0.0f, -1.0f, +0.0f),
		// Top
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f),
		glm::vec3(+0.0f, +1.0f, +0.0f)
	};

	std::vector<glm::vec3> colors = {
		// Front			
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		// Back
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		// Left
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		// Right
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		// Bottom
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		// Top
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f),
		glm::vec3(+1.0f, +1.0f, +1.0f)
	};

	std::vector<glm::vec2> textures = {
		// Front
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		// Back
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		// Left
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		// Right
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		// Bottom
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),
		// Top
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

public:
	Cube();
	Cube(float width);
	Cube(float width, float height);
	~Cube();
	std::vector<glm::vec3> createCube(const float width, const float height);
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getColors();
	std::vector<glm::vec2> getTextures();
	std::vector<unsigned int> getIndices();
	int getNumCubes();
};