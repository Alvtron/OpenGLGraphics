#include "Diamond.h"

/* Create a Diamond object that stores vertex data */
Diamond::Diamond()
{
	createDiamond(WIDTH);
}

/* Create a Diamond object that stores vertex data */
Diamond::Diamond(float width)
{
	createDiamond(width);
}

/* Create a Diamond object that stores vertex data */
Diamond::~Diamond()
{
}

void Diamond::createDiamond(float width) {
	float radius = width / 2.0f;
	vertices = {
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

	normals = {
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

	uvs = {
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

	createColors();
	calculateTangents();
}