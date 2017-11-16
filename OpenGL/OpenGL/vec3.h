#pragma once

#include <iostream>

class vec3 {

public:
	float x;
	float y;
	float z;

	vec3();
	vec3(const float & a);
	vec3(const float& a, const float& b, const float& c);

	static vec3 cross(const vec3& v1, const vec3& v2);

	static float dot(const vec3& v1, const vec3& v2);

	static float length(const vec3 & v);

	static vec3 normalize(const vec3& v);

	static vec3 midpoint(const vec3 & a, const vec3 & b);

	static vec3 scale(const vec3& v, const float& k);

	static vec3 add(const vec3& v1, const vec3& v2);
	static vec3 subtract(const vec3& v1, const vec3& v2);
	static vec3 multiply(const vec3& v1, const vec3& v2);
	static vec3 divide(const vec3& v1, const vec3& v2);

	friend vec3 operator+(const vec3& left, const vec3& right);
	friend vec3 operator-(const vec3& left, const vec3& right);
	friend vec3 operator*(const vec3& left, const vec3& right);
	friend vec3 operator/(const vec3& left, const vec3& right);
	friend vec3 operator*(const vec3& left, const float& scalar);
	friend std::ostream& operator<<(std::ostream& stream, const vec3& v);

};