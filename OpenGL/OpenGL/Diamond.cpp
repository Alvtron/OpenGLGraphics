#include "Diamond.h"

unsigned int Diamond::num_diamonds = 0;

Diamond::Diamond()
{
	num_diamonds++;
}

Diamond::Diamond(float width)
{
	vertices = createDiamond(width);
	Mesh::createVertexData(vertices, normals, colors, textures);
	num_diamonds++;
}

Diamond::~Diamond()
{
	num_diamonds--;
}

std::vector<vec3> Diamond::createDiamond(float width) {
	float radius = width / 2.0f;
	return {
		vec3(-radius, 0.0f, -radius),
		vec3(+radius, 0.0f, -radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(+radius, 0.0f, -radius),
		vec3(+radius, 0.0f, +radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(+radius, 0.0f, +radius),
		vec3(-radius, 0.0f, +radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(-radius, 0.0f, +radius),
		vec3(-radius, 0.0f, -radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(-radius, 0.0f, -radius),
		vec3(+radius, 0.0f, -radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(+radius, 0.0f, -radius),
		vec3(+radius, 0.0f, +radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(+radius, 0.0f, +radius),
		vec3(-radius, 0.0f, +radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(-radius, 0.0f, +radius),
		vec3(-radius, 0.0f, -radius),
		vec3(0.0f, -radius, 0.0f)
	};
}

std::vector<vec3> Diamond::getVertices()
{
	return vertices;
}

std::vector<vec3> Diamond::getNormals()
{
	return normals;
}

std::vector<vec3> Diamond::getColors()
{
	return colors;
}

std::vector<vec2> Diamond::getTextures()
{
	return textures;
}

int Diamond::getNumDiamonds()
{
	return num_diamonds;
}
