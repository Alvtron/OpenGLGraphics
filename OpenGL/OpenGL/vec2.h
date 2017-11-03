#pragma once

#include <iostream>

class vec2 {

public:
	float x;
	float y;

	vec2();
	vec2(const float& a, const float& b);

	friend std::ostream& operator<<(std::ostream& stream, const vec2& v);

};