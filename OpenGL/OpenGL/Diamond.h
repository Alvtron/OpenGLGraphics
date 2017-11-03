#pragma once
#include "Mesh.h"

class Diamond : public Mesh
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f, RADIUS = 0.5;
	static unsigned int num_diamonds;

	std::vector<vec3> vertices = {
		vec3(-RADIUS, 0.0f, -RADIUS),
		vec3(+RADIUS, 0.0f, -RADIUS),
		vec3(0.0f, +RADIUS, 0.0f),

		vec3(+RADIUS, 0.0f, -RADIUS),
		vec3(+RADIUS, 0.0f, +RADIUS),
		vec3(0.0f, +RADIUS, 0.0f),

		vec3(+RADIUS, 0.0f, +RADIUS),
		vec3(-RADIUS, 0.0f, +RADIUS),
		vec3(0.0f, +RADIUS, 0.0f),

		vec3(-RADIUS, 0.0f, +RADIUS),
		vec3(-RADIUS, 0.0f, -RADIUS),
		vec3(0.0f, +RADIUS, 0.0f),

		vec3(-RADIUS, 0.0f, -RADIUS),
		vec3(+RADIUS, 0.0f, -RADIUS),
		vec3(0.0f, -RADIUS, 0.0f),

		vec3(+RADIUS, 0.0f, -RADIUS),
		vec3(+RADIUS, 0.0f, +RADIUS),
		vec3(0.0f, -RADIUS, 0.0f),

		vec3(+RADIUS, 0.0f, +RADIUS),
		vec3(-RADIUS, 0.0f, +RADIUS),
		vec3(0.0f, -RADIUS, 0.0f),

		vec3(-RADIUS, 0.0f, +RADIUS),
		vec3(-RADIUS, 0.0f, -RADIUS),
		vec3(0.0f, -RADIUS, 0.0f)
	};
	std::vector<vec3> normals = {
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+0.0f, +0.0f, -1.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+1.0f, +0.0f, +0.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(+0.0f, +0.0f, +1.0f),
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(-1.0f, +0.0f, +0.0f),
		vec3(-1.0f, +0.0f, +0.0f)
	};
	std::vector<vec3> colors = {
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f),
		vec3(1.0f, 1.0f, 1.0f)
		
	};
	std::vector<vec2> textures = {
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
public:
	Diamond();
	Diamond(float width);
	~Diamond();
	std::vector<vec3> createDiamond(float width);
	std::vector<vec3> getVertices();
	std::vector<vec3> getNormals();
	std::vector<vec3> getColors();
	std::vector<vec2> getTextures();
	int getNumDiamonds();
};

