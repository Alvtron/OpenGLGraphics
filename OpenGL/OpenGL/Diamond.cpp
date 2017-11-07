#include "Diamond.h"

Diamond::Diamond() : Mesh()
{
	createDiamond(WIDTH);
}

Diamond::Diamond(float width) : Mesh()
{
	createDiamond(width);
}

Diamond::~Diamond()
{
}

void Diamond::createDiamond(float width) {
	float radius = width / 2.0f;
	vertex.vertices = {
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

	vertex.normals = {
		vec3(0.0f, 0.5f, -0.5f),
		vec3(0.0f, 0.5f, -0.5f),
		vec3(0.0f, 0.5f, -0.5f),

		vec3(0.5f, 0.5f, 0.0f),
		vec3(0.5f, 0.5f, 0.0f),
		vec3(0.5f, 0.5f, 0.0f),

		vec3(0.0f, 0.5f, 0.5f),
		vec3(0.0f, 0.5f, 0.5f),
		vec3(0.0f, 0.5f, 0.5f),

		vec3(-0.5f, 0.5f, 0.0f),
		vec3(-0.5f, 0.5f, 0.0f),
		vec3(-0.5f, 0.5f, 0.0f),

		vec3(0.0f, -0.5f, -0.5f),
		vec3(0.0f, -0.5f, -0.5f),
		vec3(0.0f, -0.5f, -0.5f),

		vec3(0.5f, -0.5f, 0.0f),
		vec3(0.5f, -0.5f, 0.0f),
		vec3(0.5f, -0.5f, 0.0f),

		vec3(0.0f, -0.5f, 0.5f),
		vec3(0.0f, -0.5f, 0.5f),
		vec3(0.0f, -0.5f, 0.5f),

		vec3(-0.5f, -0.5f, 0.0f),
		vec3(-0.5f, -0.5f, 0.0f),
		vec3(-0.5f, -0.5f, 0.0f)
	};

	vertex.uvs = {
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f)
	};

	MeshUtility::createColors(vertex);
	MeshUtility::calculateTangents(vertex);
}