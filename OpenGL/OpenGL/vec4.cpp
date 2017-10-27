#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <cmath>
#include "vec4.h"

vec4::vec4() {
	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
	w = 1.0f;
}

vec4::vec4(const GLfloat& a, const GLfloat& b, const GLfloat& c) {
	x = a;
	y = b;
	z = c;
	w = 1.0f;
}

vec4::vec4(const GLfloat& a, const GLfloat& b, const GLfloat& c, const GLfloat& d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

vec4& vec4::multiply(const mat4& m) {
	x = m.matrix[0] * x + m.matrix[4] * y + m.matrix[8] * z + m.matrix[12] * w;
	y = m.matrix[1] * x + m.matrix[5] * y + m.matrix[9] * z + m.matrix[13] * w;
	z = m.matrix[2] * x + m.matrix[6] * y + m.matrix[10] * z + m.matrix[14] * w;
	w = m.matrix[3] * x + m.matrix[7] * y + m.matrix[11] * z + m.matrix[15] * w;
	return *this;
}

vec4 vec4::multiply(const mat4& m, const vec4& v) {
	vec4 result;
	result.x = m.matrix[0] * v.x + m.matrix[4] * v.y + m.matrix[8] * v.z + m.matrix[12] * v.w;
	result.y = m.matrix[1] * v.x + m.matrix[5] * v.y + m.matrix[9] * v.z + m.matrix[13] * v.w;
	result.z = m.matrix[2] * v.x + m.matrix[6] * v.y + m.matrix[10] * v.z + m.matrix[14] * v.w;
	result.w = m.matrix[3] * v.x + m.matrix[7] * v.y + m.matrix[11] * v.z + m.matrix[15] * v.w;
	return result;
}

vec4 vec4::cross(const vec4& v1, const vec4& v2) {
	vec4 result;
	result.x = (v1.y * v2.z) - (v2.y * v1.z);
	result.y = -((v1.x * v2.z) - (v2.x * v1.z));
	result.z = (v1.x * v2.y) - (v2.x * v1.y);
	return result;
}

GLfloat vec4::dot(const vec4& v1, const vec4& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

vec4& vec4::normalize() {
	GLfloat vectorLength = sqrt((x * x) + (y * y) + (z * z));
	x /= vectorLength;
	y /= vectorLength;
	z /= vectorLength;
	return *this;
}

vec4 vec4::normalize(const vec4& v) {
	vec4 result;
	GLfloat vectorLength = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	result.x = v.x / vectorLength;
	result.y = v.y / vectorLength;
	result.z = v.z / vectorLength;
	return result;
}

vec4& vec4::add(const vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec4& vec4::subtract(const vec4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec4& vec4::multiply(const vec4& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vec4& vec4::divide(const vec4& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

vec4 operator+(vec4 left, const vec4& right) {
	return left.add(right);
}

vec4 operator-(vec4 left, const vec4& right) {
	return left.subtract(right);
}

vec4 operator*(vec4 left, const vec4& right) {
	return left.multiply(right);
}

vec4 operator*(vec4 left, const mat4& right) {
	return left.multiply(right);
}

vec4 operator/(vec4 left, const vec4& right) {
	return left.divide(right);
}

vec4& vec4::operator+=(const vec4& v) {
	return add(v);
}

vec4& vec4::operator-=(const vec4& v) {
	return subtract(v);
}

vec4& vec4::operator*=(const vec4& v) {
	return multiply(v);
}

vec4& vec4::operator*=(const mat4& m) {
	return multiply(m);
}

vec4& vec4::operator/=(const vec4& v) {
	return divide(v);
}

std::ostream& operator<<(std::ostream& stream, const vec4& v) {
	stream << "vec4:\n(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return stream;
}
