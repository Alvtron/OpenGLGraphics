#pragma once

#include <iostream>
#include "vec3.h"

class mat4 {

public:
	float matrix[16];

	mat4();
	static mat4 makeIdentity();
	static mat4 makeScale(const vec3& scale);
	static mat4 makeRotate(const float& angle, const vec3& axis);
	static mat4 makeTranslate(const vec3& translation);
	static mat4 makePerspective(const float& angle, const float& aspectRatio, const float& near, const float& far);
	static mat4 makeOrtho(const float& l, const float& r, const float& b, const float& t);

	static mat4 removeTranslation(const mat4& m);

	static mat4 multiply(const mat4& m1, const mat4& m2);
	friend mat4 operator*(const mat4& left, const mat4& right);

	friend std::ostream& operator<<(std::ostream& stream, const mat4& m);

};