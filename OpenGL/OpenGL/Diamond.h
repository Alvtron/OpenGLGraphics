#pragma once
#include "Mesh.h"

class Diamond : public Mesh
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f, RADIUS = 0.5;
	static unsigned int num_diamonds;

	std::vector<glm::vec3> vertices = {
		glm::vec3(-RADIUS, 0.0f, -RADIUS),
		glm::vec3(+RADIUS, 0.0f, -RADIUS),
		glm::vec3(0.0f, +RADIUS, 0.0f),

		glm::vec3(+RADIUS, 0.0f, -RADIUS),
		glm::vec3(+RADIUS, 0.0f, +RADIUS),
		glm::vec3(0.0f, +RADIUS, 0.0f),

		glm::vec3(+RADIUS, 0.0f, +RADIUS),
		glm::vec3(-RADIUS, 0.0f, +RADIUS),
		glm::vec3(0.0f, +RADIUS, 0.0f),

		glm::vec3(-RADIUS, 0.0f, +RADIUS),
		glm::vec3(-RADIUS, 0.0f, -RADIUS),
		glm::vec3(0.0f, +RADIUS, 0.0f),

		glm::vec3(-RADIUS, 0.0f, -RADIUS),
		glm::vec3(+RADIUS, 0.0f, -RADIUS),
		glm::vec3(0.0f, -RADIUS, 0.0f),

		glm::vec3(+RADIUS, 0.0f, -RADIUS),
		glm::vec3(+RADIUS, 0.0f, +RADIUS),
		glm::vec3(0.0f, -RADIUS, 0.0f),

		glm::vec3(+RADIUS, 0.0f, +RADIUS),
		glm::vec3(-RADIUS, 0.0f, +RADIUS),
		glm::vec3(0.0f, -RADIUS, 0.0f),

		glm::vec3(-RADIUS, 0.0f, +RADIUS),
		glm::vec3(-RADIUS, 0.0f, -RADIUS),
		glm::vec3(0.0f, -RADIUS, 0.0f)
	};
	std::vector<glm::vec3> normals = {
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+0.0f, +0.0f, -1.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+1.0f, +0.0f, +0.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(+0.0f, +0.0f, +1.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f),
		glm::vec3(-1.0f, +0.0f, +0.0f)
	};
	std::vector<glm::vec3> colors = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
		
	};
	std::vector<glm::vec2> textures = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f)
	};
public:
	Diamond();
	Diamond(float width);
	~Diamond();
	std::vector<glm::vec3> createDiamond(float width);
	std::vector<glm::vec3> getVertices();
	std::vector<glm::vec3> getNormals();
	std::vector<glm::vec3> getColors();
	std::vector<glm::vec2> getTextures();
	int getNumDiamonds();
};

