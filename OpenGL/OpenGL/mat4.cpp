#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <cmath>
#include "mat4.h"

mat4::mat4() {
	for (GLint i = 0; i < 16; i++)
		matrix[i] = 0.0f;
}

mat4 mat4::makeIdentity() {

	mat4 result;

	result.matrix[0] = 1.0f;
	result.matrix[5] = 1.0f;
	result.matrix[10] = 1.0f;
	result.matrix[15] = 1.0f;

	return result;

}

mat4 mat4::makeScale(const vec3& scale) {

	mat4 result;

	result.matrix[0] = scale.x;
	result.matrix[5] = scale.y;
	result.matrix[10] = scale.z;
	result.matrix[15] = 1.0f;

	return result;

}

mat4 mat4::makeRotate(const GLfloat& angle, const vec3& axis) {

	mat4 result;

	GLfloat r = (GLfloat)(angle * (M_PI / 180));
	GLfloat cosine = (GLfloat)cos((GLdouble)r);
	GLfloat sine = (GLfloat)sin((GLdouble)r);
	GLfloat omc = 1.0f - cosine;

	result.matrix[0] = axis.x * omc + cosine;
	result.matrix[1] = axis.y * axis.x * omc + axis.z * sine;
	result.matrix[2] = axis.x * axis.z * omc - axis.y * sine;

	result.matrix[4] = axis.x * axis.y * omc - axis.z * sine;
	result.matrix[5] = axis.y * omc + cosine;
	result.matrix[6] = axis.y * axis.z * omc + axis.x * sine;

	result.matrix[8] = axis.x * axis.z * omc + axis.y * sine;
	result.matrix[9] = axis.y * axis.z * omc - axis.x * sine;
	result.matrix[10] = axis.z * omc + cosine;

	result.matrix[15] = 1.0f;

	return result;

}

mat4 mat4::makeTranslate(const vec3& translation) {

	mat4 result = makeIdentity();

	result.matrix[12] = translation.x;
	result.matrix[13] = translation.y;
	result.matrix[14] = translation.z;

	return result;

}

mat4 mat4::makePerspective(const GLfloat& angle, const GLfloat& aspectRatio, const GLfloat& n, const GLfloat& f) {

	mat4 result;

	GLfloat t = tan(angle / 2.0f) * n;
	GLfloat b = -t;
	GLfloat r = t * aspectRatio;
	GLfloat l = -t * aspectRatio;

	result.matrix[0] = (2.0f * n) / (r - l);
	result.matrix[5] = (2.0f * n) / (t - b);
	result.matrix[8] = (r + l) / (r - l);
	result.matrix[9] = (t + b) / (t - b);
	result.matrix[10] = -((f + n) / (f - n));
	result.matrix[11] = -1.0f;
	result.matrix[14] = -((2.0f * f * n) / (f - n));

	return result;

}

mat4 mat4::multiply(const mat4& m1, const mat4& m2) {

	mat4 result;

	for (GLint i = 0; i < 4; i++) {
		for (GLint j = 0; j < 4; j++) {
			for (GLint k = 0; k < 4; k++) {
				result.matrix[i + j * 4] += m1.matrix[i + k * 4] * m2.matrix[k + j * 4];
			}
		}
	}

	return result;

}

mat4 operator*(const mat4& left, const mat4& right) {
	return mat4::multiply(left, right);
}

std::ostream& operator<<(std::ostream& stream, const mat4& m) {
	stream << "mat4: \n" <<
	m.matrix[0] << "\t" << m.matrix[1] << "\t" << m.matrix[2] << "\t" << m.matrix[3] << "\n" << 
	m.matrix[4] << "\t" << m.matrix[5] << "\t" << m.matrix[6] << "\t" << m.matrix[7] << "\n" <<
	m.matrix[8] << "\t" << m.matrix[9] << "\t" << m.matrix[10] << "\t" << m.matrix[11] << "\n" <<
	m.matrix[12] << "\t" << m.matrix[13] << "\t" << m.matrix[14] << "\t" << m.matrix[15];
	return stream;
}