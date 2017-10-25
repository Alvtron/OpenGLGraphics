#pragma once

#include <GL/glew.h>
#include <iostream>
#include "mat4.h"

class vec4 {

public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;

	vec4();
	vec4(const GLfloat& a, const GLfloat& b, const GLfloat& c, const GLfloat& d);
	vec4(const GLfloat& a, const GLfloat& b, const GLfloat& c);

	vec4& multiply(const mat4& m);
	static vec4 multiply(const mat4& m, const vec4& v);

	static vec4 cross(const vec4& v1, const vec4& v2);

	static GLfloat dot(const vec4& v1, const vec4& v2);

	vec4& normalize();
	static vec4 normalize(const vec4& v1);

	vec4& add(const vec4& v);
	vec4& subtract(const vec4& v);
	vec4& multiply(const vec4& v);
	vec4& divide(const vec4& v);

	friend vec4 operator+(vec4 left, const vec4& right);
	friend vec4 operator-(vec4 left, const vec4& right);
	friend vec4 operator*(vec4 left, const vec4& right);
	friend vec4 operator*(vec4 left, const mat4& right);
	friend vec4 operator/(vec4 left, const vec4& right);

	vec4& operator+=(const vec4& v);
	vec4& operator-=(const vec4& v);
	vec4& operator*=(const vec4& v);
	vec4& operator*=(const mat4& m);
	vec4& operator/=(const vec4& v);

	friend std::ostream& operator<<(std::ostream& stream, const vec4& v);

}; 