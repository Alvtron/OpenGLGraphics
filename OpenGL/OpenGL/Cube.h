#ifndef CUBE_HEADER
#define CUBE_HEADER

#include "Mesh.h"

class Cube : public Mesh
{
private:
	static unsigned int num_cubes;

	const std::vector<float> VERTICES = {
		// Front
		-0.5f, -0.5f, -0.5f,	
		+0.5f, -0.5f, -0.5f,	
		+0.5f, +0.5f, -0.5f,	
		-0.5f, +0.5f, -0.5f,	
		// Back
		-0.5f, -0.5f, +0.5f,	
		+0.5f, -0.5f, +0.5f,	
		+0.5f, +0.5f, +0.5f,	
		-0.5f, +0.5f, +0.5f,	
		// Left
		-0.5f, -0.5f, +0.5f,	
		-0.5f, -0.5f, -0.5f,	
		-0.5f, +0.5f, -0.5f,	
		-0.5f, +0.5f, +0.5f,	
		// Right
		+0.5f, -0.5f, -0.5f,	
		+0.5f, -0.5f, +0.5f,	
		+0.5f, +0.5f, +0.5f,	
		+0.5f, +0.5f, -0.5f,	
		// Bottom
		-0.5f, -0.5f, -0.5f,	
		+0.5f, -0.5f, -0.5f,	
		+0.5f, -0.5f, +0.5f,	
		-0.5f, -0.5f, +0.5f,	
		// Top
		-0.5f, +0.5f, -0.5f,	
		+0.5f, +0.5f, -0.5f,	
		+0.5f, +0.5f, +0.5f,	
		-0.5f, +0.5f, +0.5f	
	};

	const std::vector<float> NORMALS = {
		// Front
		+0.0f, +0.0f, -1.0f,
		+0.0f, +0.0f, -1.0f,
		+0.0f, +0.0f, -1.0f,
		+0.0f, +0.0f, -1.0f,
		// Back
		+0.0f, +0.0f, +1.0f,
		+0.0f, +0.0f, +1.0f,
		+0.0f, +0.0f, +1.0f,
		+0.0f, +0.0f, +1.0f,
		// Left
		-1.0f, +0.0f, +0.0f,
		-1.0f, +0.0f, +0.0f,
		-1.0f, +0.0f, +0.0f,
		-1.0f, +0.0f, +0.0f,
		// Right
		+1.0f, +0.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,
		+1.0f, +0.0f, +0.0f,
		// Bottom
		+0.0f, -1.0f, +0.0f,
		+0.0f, -1.0f, +0.0f,
		+0.0f, -1.0f, +0.0f,
		+0.0f, -1.0f, +0.0f,
		// Top
		+0.0f, +1.0f, +0.0f,
		+0.0f, +1.0f, +0.0f,
		+0.0f, +1.0f, +0.0f,
		+0.0f, +1.0f, +0.0f
	};

	const std::vector<float> COLORS = {
		// Front			
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		// Back
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		// Left
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		// Right
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		// Bottom
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		// Top
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +1.0f
	};

	const std::vector<float> TEXTURES = {
		// Front
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Back
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Left
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Right
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Bottom
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		// Top
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	const std::vector<unsigned int> INDICES = {
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
	static const unsigned int VERTICES_ARRAY_SIZE = 72;
	static const unsigned int NORMALS_ARRAY_SIZE = 72;
	static const unsigned int COLORS_ARRAY_SIZE = 72;
	static const unsigned int TEXTURES_ARRAY_SIZE = 48;
	static const unsigned int INDICES_ARRAY_SIZE = 36;

	Cube();
	~Cube();
	int getNumCubes();
};

#endif