#ifndef RECT_HEADER
#define RECT_HEADER

#include "Mesh.h"

class Rect : public Mesh
{
private:

	static unsigned int num_rectangles;

	enum CORNERS : int
	{
		Ax = 0, Ay = 1, Az = 2,
		Bx = 3, By = 4, Bz = 5, 
		Cx = 6, Cy = 7, Cz = 8, 
		Dx = 9, Dy = 10, Dz = 11 
	};

	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	const static unsigned int VERTICES_ARRAY_SIZE = 12;
	const static unsigned int NORMALS_ARRAY_SIZE = 12;
	const static unsigned int COLORS_ARRAY_SIZE = 12;
	const static unsigned int TEXTURE_ARRAY_SIZE = 8;
	const static unsigned int INDICES_ARRAY_SIZE = 6;

	std::vector<float> vertices = {
		-(WIDTH / 2.0f), -(HEIGHT / 2.0f), 0.0f,
		+(WIDTH / 2.0f), -(HEIGHT / 2.0f), 0.0f,
		+(WIDTH / 2.0f), +(HEIGHT / 2.0f), 0.0f,
		-(WIDTH / 2.0f), +(HEIGHT / 2.0f), 0.0f
	};					 
	const std::vector<float> NORMALS = {
		+0.0f, +0.0f, -1.0f,
		+0.0f, +0.0f, -1.0f,
		+0.0f, +0.0f, -1.0f,
		+0.0f, +0.0f, -1.0f
	};
	std::vector<float> colors = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};
	const std::vector<float> TEXTURES = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
	const std::vector<unsigned int> INDICES = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

public:

	Rect();
	Rect(float width, float height);
	~Rect();

	float getWidth();
	float getHeight();
	float getAreal();
	int getNumRectangles();
};

#endif