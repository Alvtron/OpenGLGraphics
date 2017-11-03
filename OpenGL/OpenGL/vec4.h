#pragma once

#include <iostream>

class vec4 {

public:
	float x;
	float y;
	float z;
	float w;

	vec4();
	vec4(const float& a, const float& b, const float& c, const float& d);
	vec4(const float& a, const float& b, const float& c);

	static vec4 multiply(const mat4& m, const vec4& v);

	static vec4 cross(const vec4& v1, const vec4& v2);

	static float dot(const vec4& v1, const vec4& v2);

	vec4& normalize();
	static vec4 normalize(const vec4& v1);

	static vec4 add(const vec4& v1, const vec4& v2);
	static vec4 subtract(const vec4& v1, const vec4& v2);
	static vec4 multiply(const vec4& v1, const vec4& v2);
	static vec4 divide(const vec4& v1, const vec4& v2);

	static vec4 scale(const vec4& v, const float& k);

	friend vec4 operator+(const vec4& left, const vec4& right);
	friend vec4 operator-(const vec4& left, const vec4& right);
	friend vec4 operator*(const vec4& left, const vec4& right);
	friend vec4 operator*(const mat4& left, const vec4& right);
	friend vec4 operator/(const vec4& left, const vec4& right);

	static float* vec4::getArray(const vec4& v);

	friend std::ostream& operator<<(std::ostream& stream, const vec4& v);

}; 