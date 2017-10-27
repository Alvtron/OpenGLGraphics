#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <cmath>
#include "vec3.h"

vec3::vec3() {
	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
}

vec3::vec3(const GLfloat& a, const GLfloat& b, const GLfloat& c) {
	x = a;
	y = b;
	z = c;
}

vec3 vec3::cross(const vec3& v1, const vec3& v2) {
	vec3 result;
	result.x = (v1.y * v2.z) - (v2.y * v1.z);
	result.y = -((v1.x * v2.z) - (v2.x * v1.z));
	result.z = (v1.x * v2.y) - (v2.x * v1.y);
	return result;
}

GLfloat vec3::dot(const vec3& v1, const vec3& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

vec3& vec3::normalize() {
	GLfloat vectorLength = sqrt((x * x) + (y * y) + (z * z));
	x /= vectorLength;
	y /= vectorLength;
	z /= vectorLength;
	return *this;
}

vec3 vec3::normalize(const vec3& v) {
	vec3 result;
	GLfloat vectorLength = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.x = v.x / vectorLength;
	result.y = v.y / vectorLength;
	result.z = v.z / vectorLength;
	return result;
}

vec3& vec3::add(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec3& vec3::subtract(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec3& vec3::multiply(const vec3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vec3& vec3::divide(const vec3& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

vec3 operator+(vec3 left, const vec3& right) {
	return left.add(right);
}

vec3 operator-(vec3 left, const vec3& right) {
	return left.subtract(right);
}

vec3 operator*(vec3 left, const vec3& right) {
	return left.multiply(right);
}

vec3 operator/(vec3 left, const vec3& right) {
	return left.divide(right);
}

vec3& vec3::operator+=(const vec3& v) {
	return add(v);
}

vec3& vec3::operator-=(const vec3& v) {
	return subtract(v);
}

vec3& vec3::operator*=(const vec3& v) {
	return multiply(v);
}

vec3& vec3::operator/=(const vec3& v) {
	return divide(v);
}

std::ostream& operator<<(std::ostream& stream, const vec3& v) {
	stream << "vec3:\n(" << v.x << ", " << v.y << ", " << v.z << ")";
	return stream;
}
