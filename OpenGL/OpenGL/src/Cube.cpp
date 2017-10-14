#include "Cube.h"
#include <cmath>

unsigned int Cube::num_cubes = 0;

Cube::Cube()
{
	vertices = VERTICES;
	normals = NORMALS;
	colors = COLORS;
	textures = TEXTURES;
	indices = INDICES;
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
