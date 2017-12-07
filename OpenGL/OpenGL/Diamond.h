#pragma once
#include "Vertex.h"

class Diamond : public Vertex
{
private:
	const float WIDTH = 1.0f, HEIGHT = 1.0f, RADIUS = 0.5;
	/* Create the Diamond object. */
	void createDiamond(float width);
public:
	/* Create a Diamond object with default sizes. */
	Diamond();
	/* Create a Diamond object with width */
	Diamond(float width);
	/* De-constructor */
	~Diamond();
};

