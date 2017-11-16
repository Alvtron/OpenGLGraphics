#include "vec3.h"

vec3::vec3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

vec3::vec3(const float& a) {
	x = a;
	y = a;
	z = a;
}

vec3::vec3(const float& a, const float& b, const float& c) {
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

float vec3::dot(const vec3& v1, const vec3& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float vec3::length(const vec3& v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

vec3 vec3::normalize(const vec3& v) {
	float vectorLength = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return vec3(v.x / vectorLength, v.y / vectorLength, v.z / vectorLength);
}

vec3 vec3::midpoint(const vec3 &a, const vec3 &b) {
	return vec3((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
}

vec3 vec3::add(const vec3& v1, const vec3& v2) {
	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3 vec3::subtract(const vec3& v1, const vec3& v2) {
	return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3 vec3::multiply(const vec3& v1, const vec3& v2) {
	return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

vec3 vec3::divide(const vec3& v1, const vec3& v2) {
	return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

vec3 vec3::scale(const vec3& v, const float& k) {
	return vec3(v.x * k, v.y * k, v.z * k);
}

vec3 operator+(const vec3& left, const vec3& right) {
	return vec3::add(left, right);
}

vec3 operator-(const vec3& left, const vec3& right) {
	return vec3::subtract(left, right);
}

vec3 operator*(const vec3& left, const vec3& right) {
	return vec3::multiply(left, right);
}

vec3 operator*(const vec3& left, const float& scalar) {
	return vec3(left.x * scalar, left.y * scalar, left.z * scalar);
}

vec3 operator/(const vec3& left, const vec3& right) {
	return vec3::divide(left, right);
}

std::ostream& operator<<(std::ostream& stream, const vec3& v) {
	stream << "vec3:\n(" << v.x << ", " << v.y << ", " << v.z << ")";
	return stream;
}
