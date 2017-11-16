#pragma once

#include <iostream>

class vec2 {

public:
	float x;
	float y;

	vec2();
	vec2(const float& a, const float& b);

	friend std::ostream& operator<<(std::ostream& stream, const vec2& v);

	static float dot(const vec2& v1, const vec2& v2);

	static float length(const vec2 & v);

	static vec2 normalize(const vec2& v);

	static vec2 midpoint(const vec2 & a, const vec2 & b);

	static vec2 scale(const vec2& v, const float& k);

	static vec2 add(const vec2& v1, const vec2& v2);
	static vec2 subtract(const vec2& v1, const vec2& v2);
	static vec2 multiply(const vec2& v1, const vec2& v2);
	static vec2 divide(const vec2& v1, const vec2& v2);

	friend vec2 operator+(const vec2& left, const vec2& right);
	friend vec2 operator-(const vec2& left, const vec2& right);
	friend vec2 operator*(const vec2& left, const vec2& right);
	friend vec2 operator/(const vec2& left, const vec2& right);
	friend vec2 operator*(const vec2& left, const float& scalar);
};