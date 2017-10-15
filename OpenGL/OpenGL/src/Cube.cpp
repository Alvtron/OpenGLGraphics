#include "Cube.h"
#include <cmath>

unsigned int Cube::num_cubes = 0;

Cube::Cube() : Mesh()
{
	Mesh::createVertexData(VERTICES, NORMALS, COLORS, TEXTURES, INDICES);
	num_cubes++;
}

Cube::~Cube()
{
	num_cubes--;
}

int Cube::getNumCubes()
{
	return num_cubes;
}
