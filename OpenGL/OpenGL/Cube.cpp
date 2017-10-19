#include "Cube.h"
#include <cmath>

unsigned int Cube::num_cubes = 0; 

/* Create a Cube object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to add vertex data. */
Cube::Cube() : Mesh()
{
	Mesh::createVertexData(VERTICES, NORMALS, COLORS, TEXTURES, INDICES);
	num_cubes++;
}

/* Deconstructor */
Cube::~Cube()
{
	num_cubes--;
}

/* Return number of cubes created on this stack */
int Cube::getNumCubes()
{
	return num_cubes;
}