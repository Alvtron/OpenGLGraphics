#include "mat4.h"
#include "vec4.h"


vec4::vec4() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}

vec4::vec4(const float& a, const float& b, const float& c) {
	x = a;
	y = b;
	z = c;
	w = 1.0f;
}

vec4::vec4(const float& a, const float& b, const float& c, const float& d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

vec4 vec4::multiply(const mat4& m, const vec4& v) {
	return vec4(m.matrix[0] * v.x + m.matrix[4] * v.y + m.matrix[8] * v.z + m.matrix[12] * v.w,
				m.matrix[1] * v.x + m.matrix[5] * v.y + m.matrix[9] * v.z + m.matrix[13] * v.w,
				m.matrix[2] * v.x + m.matrix[6] * v.y + m.matrix[10] * v.z + m.matrix[14] * v.w,
				m.matrix[3] * v.x + m.matrix[7] * v.y + m.matrix[11] * v.z + m.matrix[15] * v.w);
}

vec4 vec4::cross(const vec4& v1, const vec4& v2) {
	return vec4((v1.y * v2.z) - (v2.y * v1.z), -((v1.x * v2.z) - (v2.x * v1.z)), (v1.x * v2.y) - (v2.x * v1.y));
}

float vec4::dot(const vec4& v1, const vec4& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

vec4 vec4::normalize(const vec4& v) {
	float vectorLength = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return vec4(v.x / vectorLength, v.y / vectorLength, v.z / vectorLength, 1.0f);
}

vec4 vec4::add(const vec4& v1, const vec4& v2) {
	return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, 1.0f);
}

vec4 vec4::subtract(const vec4& v1, const vec4& v2) {
	return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, 1.0f);
}

vec4 vec4::multiply(const vec4& v1, const vec4& v2) {
	return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, 1.0f);
}

vec4 vec4::divide(const vec4& v1, const vec4& v2) {
	return vec4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, 1.0f);
}

vec4 vec4::scale(const vec4& v, const float& k) {
	return vec4(v.x * k, v.y * k, v.z * k, 1.0f);
}

vec4 operator+(const vec4& left, const vec4& right) {
	return vec4::add(left, right);
}

vec4 operator-(const vec4& left, const vec4& right) {
	return vec4::subtract(left, right);
}

vec4 operator*(const vec4& left, const vec4& right) {
	return vec4::multiply(left, right);
}

vec4 operator*(const mat4& left, const vec4& right) {
	return vec4::multiply(left, right);
}

vec4 operator/(const vec4& left, const vec4& right) {
	return vec4::divide(left, right);
}

std::ostream& operator<<(std::ostream& stream, const vec4& v) {
	stream << "vec4:\n(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return stream;
}
