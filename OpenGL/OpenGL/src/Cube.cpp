#include "Cube.h"
#include <cmath>

unsigned int Cube::num_cubes = 0;

Cube::Cube() : Mesh()
{
	//Mesh::createVertexData(VERTICES, NORMALS, COLORS, TEXTURES, INDICES);
	addVertexData(VERTICES, MESH_VERTICE);
	addVertexData(NORMALS, MESH_NORMAL);
	addVertexData(COLORS, MESH_COLOR);
	addVertexData(TEXTURES, MESH_TEXTURE);
	addIndices(INDICES);

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
