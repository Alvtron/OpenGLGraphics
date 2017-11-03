#pragma once

#include <iostream>

class mat2 {

public:
	float matrix[4];

	mat2();

	friend std::ostream& operator<<(std::ostream& stream, const mat2& m);

};