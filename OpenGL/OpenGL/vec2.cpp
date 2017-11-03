#include "vec2.h"

vec2::vec2() {
	x = 1.0f;
	y = 1.0f;
}

vec2::vec2(const float& a, const float& b) {
	x = a;
	y = b;
}

std::ostream& operator<<(std::ostream& stream, const vec2& v) {
	stream << "vec2:\n(" << v.x << ", " << v.y << ")";
	return stream;
}