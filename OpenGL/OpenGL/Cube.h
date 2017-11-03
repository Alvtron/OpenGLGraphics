#pragma once
#include "Mesh.h"

class Cube : public Mesh
{
private:
	static unsigned int num_cubes;

	std::vector<vec3> vertices = {
		// Front
		vec3(-0.5f, -0.5f, -0.5f),
		vec3(+0.5f, -0.5f, -0.5f),	
		vec3(+0.5f, +0.5f, -0.5f),	
		vec3(-0.5f, +0.5f, -0.5f),	
		// Back
		vec3(-0.5f, -0.5f, +0.5f),	
		vec3(+0.5f, -0.5f, +0.5f),	
		vec3(+0.5f, +0.5f, +0.5f),	
		vec3(-0.5f, +0.5f, +0.5f),	
		// Left
		vec3(-0.5f, -0.5f, +0.5f),	
		vec3(-0.5f, -0.5f, -0.5f),	
		vec3(-0.5f, +0.5f, -0.5f),	
		vec3(-0.5f, +0.5f, +0.5f),	
		// Right
		vec3(+0.5f, -0.5f, -0.5f),	
		vec3(+0.5f, -0.5f, +0.5f),	
		vec3(+0.5f, +0.5f, +0.5f),	
		vec3(+0.5f, +0.5f, -0.5f),	
		// Bottom
		vec3(-0.5f, -0.5f, -0.5f),	
		vec3(+0.5f, -0.5f, -0.5f),	
		vec3(+0.5f, -0.5f, +0.5f),	
		vec3(-0.5f, -0.5f, +0.5f),	
		// Top
		vec3(-0.5f, +0.5f, -0.5f),	
		vec3(+0.5f, +0.5f, -0.5f),	
		vec3(+0.5f, +0.5f, +0.5f),	
		vec3(-0.5f, +0.5f, +0.5f)	
	};

	std::vector<vec3> normals = {
		// Front
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		// Back
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		// Left
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(-1.0f, +0.0f, +0.0f),
		// Right
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		// Bottom
		vec3(+0.0f, -1.0f, +0.0f),
		vec3(+0.0f, -1.0f, +0.0f),
		vec3(+0.0f, -1.0f, +0.0f),
		vec3(+0.0f, -1.0f, +0.0f),
		// Top
		vec3(+0.0f, +1.0f, +0.0f),
		vec3(+0.0f, +1.0f, +0.0f),
		vec3(+0.0f, +1.0f, +0.0f),
		vec3(+0.0f, +1.0f, +0.0f)
	};

	std::vector<vec3> colors = {
		// Front			
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		// Back
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		// Left
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		// Right
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		// Bottom
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		// Top
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f),
		vec3(+1.0f, +1.0f, +1.0f)
	};

	std::vector<vec2> textures = {
		// Front
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f),
		// Back
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f),
		// Left
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f),
		// Right
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f),
		vec2(0.0f, 1.0f),
		// Bottom
		vec2(0.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 0.0f),
		// Top
		vec2(0.0f, 1.0f),
		vec2(1.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 0.0f)
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
	std::vector<vec3> createCube(const float width, const float height);
	std::vector<vec3> getVertices();
	std::vector<vec3> getNormals();
	std::vector<vec3> getColors();
	std::vector<vec2> getTextures();
	std::vector<unsigned int> getIndices();
	int getNumCubes();
};