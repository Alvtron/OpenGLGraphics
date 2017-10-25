#pragma once

#include <GL/glew.h>
#include <iostream>
#include "vec3.h"

class mat4 {

public:
	GLfloat matrix[16];

	mat4();
	static mat4 makeIdentity();
	static mat4 makeScale(const vec3& scale);
	static mat4 makeRotate(const GLfloat& angle, const vec3& axis);
	static mat4 makeTranslate(const vec3& translation);
	static mat4 makePerspective(const GLfloat& angle, const GLfloat& aspectRatio, const GLfloat& near, const GLfloat& far);

	static mat4 multiply(const mat4& m1, const mat4& m2);
	friend mat4 operator*(const mat4& left, const mat4& right);

	friend std::ostream& operator<<(std::ostream& stream, const mat4& m);

};