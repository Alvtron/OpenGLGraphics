#include "vec2.h"

vec2::vec2() {
	x = 0.0f;
	y = 0.0f;
}

vec2::vec2(const float& a, const float& b) {
	x = a;
	y = b;
}

float vec2::dot(const vec2& v1, const vec2& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float vec2::length(const vec2& v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

vec2 vec2::normalize(const vec2& v) {
	float vectorLength = sqrt((v.x * v.x) + (v.y * v.y));
	return vec2(v.x / vectorLength, v.y / vectorLength);
}

vec2 vec2::midpoint(const vec2 &a, const vec2 &b) {
	return vec2((a.x + b.x) / 2, (a.y + b.y) / 2);
}

vec2 vec2::add(const vec2& v1, const vec2& v2) {
	return vec2(v1.x + v2.x, v1.y + v2.y);
}

vec2 vec2::subtract(const vec2& v1, const vec2& v2) {
	return vec2(v1.x - v2.x, v1.y - v2.y);
}

vec2 vec2::multiply(const vec2& v1, const vec2& v2) {
	return vec2(v1.x * v2.x, v1.y * v2.y);
}

vec2 vec2::divide(const vec2& v1, const vec2& v2) {
	return vec2(v1.x / v2.x, v1.y / v2.y);
}

vec2 vec2::scale(const vec2& v, const float& k) {
	return vec2(v.x * k, v.y * k);
}

vec2 operator+(const vec2& left, const vec2& right) {
	return vec2::add(left, right);
}

vec2 operator-(const vec2& left, const vec2& right) {
	return vec2::subtract(left, right);
}

vec2 operator*(const vec2& left, const vec2& right) {
	return vec2::multiply(left, right);
}

vec2 operator*(const vec2& left, const float& scalar) {
	return vec2(left.x * scalar, left.y * scalar);
}

vec2 operator/(const vec2& left, const vec2& right) {
	return vec2::divide(left, right);
}

std::ostream& operator<<(std::ostream& stream, const vec2& v) {
	stream << "vec2:\n(" << v.x << ", " << v.y << ")";
	return stream;
}
