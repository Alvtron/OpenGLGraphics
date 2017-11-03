#pragma once

#include <iostream>

class vec3 {

public:
	float x;
	float y;
	float z;

	vec3();
	vec3(const float& a, const float& b, const float& c);

	static vec3 cross(const vec3& v1, const vec3& v2);

	static float dot(const vec3& v1, const vec3& v2);

	vec3& normalize();
	static vec3 normalize(const vec3& v1);

	static vec3 add(const vec3& v1, const vec3& v2);
	static vec3 subtract(const vec3& v1, const vec3& v2);
	static vec3 multiply(const vec3& v1, const vec3& v2);
	static vec3 divide(const vec3& v1, const vec3& v2);

	static vec3 scale(const vec3& v, const float& k);

	friend vec3 operator+(const vec3& left, const vec3& right);
	friend vec3 operator-(const vec3& left, const vec3& right);
	friend vec3 operator*(const vec3& left, const vec3& right);
	friend vec3 operator/(const vec3& left, const vec3& right);

	static float* getArray(const vec3& v);

	friend std::ostream& operator<<(std::ostream& stream, const vec3& v);

};