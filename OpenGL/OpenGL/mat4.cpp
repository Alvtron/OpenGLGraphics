#include "mat4.h"
#include "MathDefinitions.h"

mat4::mat4() {
	for (int i = 0; i < 16; i++)
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

mat4 mat4::makeRotate(const float& angle, const vec3& axis) {

	float r = (float)(angle * (M_PI / 180.0f));

	mat4 result;

	float c = (float)cos((double)r);
	float s = (float)sin((double)r);
	float omc = 1.0f - c;

	vec3 v = vec3::normalize(axis);

	result.matrix[0] = c + omc * v.x * v.x;
	result.matrix[1] = omc * v.x * v.y + s * v.z;
	result.matrix[2] = omc * v.x * v.z - s * v.y;

	result.matrix[4] = omc * v.y * v.x - s * v.z;
	result.matrix[5] = c + omc * v.y * v.y;
	result.matrix[6] = omc * v.y * v.z + s * v.x;

	result.matrix[8] = omc * v.z * v.x + s * v.y;
	result.matrix[9] = omc * v.z * v.y - s * v.x;
	result.matrix[10] = c + omc * v.z * v.z;

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

mat4 mat4::makePerspective(const float& angle, const float& aspectRatio, const float& n, const float& f) {

	float a = (float)(angle * (M_PI / 180.0f));

	mat4 result;

	float t = tan(a / 2.0f) * n;
	float b = -t;
	float r = t * aspectRatio;
	float l = -t * aspectRatio;

	result.matrix[0] = (2.0f * n) / (r - l);
	result.matrix[5] = (2.0f * n) / (t - b);
	result.matrix[8] = (r + l) / (r - l);
	result.matrix[9] = (t + b) / (t - b);
	result.matrix[10] = -((f + n) / (f - n));
	result.matrix[11] = -1.0f;
	result.matrix[14] = -((2.0f * f * n) / (f - n));

	return result;

}

mat4 mat4::makeOrtho(const float& l, const float& r, const float& b, const float& t) {

	mat4 result;

	result.matrix[0] = 2.0f / (r - l);
	result.matrix[5] = 2.0f / (t - b);
	result.matrix[10] = -1.0f;
	result.matrix[12] = -((r + l) / (r - l));
	result.matrix[13] = -((t + b) / (t - b));
	result.matrix[15] = 1.0f;

	return result;

}

mat4 mat4::removeTranslation(const mat4& m) {
	
	mat4 result = m;

	result.matrix[12] = 0.0f;
	result.matrix[13] = 0.0f;
	result.matrix[14] = 0.0f;

	return result;

}

mat4 mat4::multiply(const mat4& m1, const mat4& m2) {

	mat4 result;

	result.matrix[0] = m1.matrix[0] * m2.matrix[0] + m1.matrix[4] * m2.matrix[1] + m1.matrix[8] * m2.matrix[2] + m1.matrix[12] * m2.matrix[3];
	result.matrix[4] = m1.matrix[0] * m2.matrix[4] + m1.matrix[4] * m2.matrix[5] + m1.matrix[8] * m2.matrix[6] + m1.matrix[12] * m2.matrix[7];
	result.matrix[8] = m1.matrix[0] * m2.matrix[8] + m1.matrix[4] * m2.matrix[9] + m1.matrix[8] * m2.matrix[10] + m1.matrix[12] * m2.matrix[11];
	result.matrix[12] = m1.matrix[0] * m2.matrix[12] + m1.matrix[4] * m2.matrix[13] + m1.matrix[8] * m2.matrix[14] + m1.matrix[12] * m2.matrix[15];
	result.matrix[1] = m1.matrix[1] * m2.matrix[0] + m1.matrix[5] * m2.matrix[1] + m1.matrix[9] * m2.matrix[2] + m1.matrix[13] * m2.matrix[3];
	result.matrix[5] = m1.matrix[1] * m2.matrix[4] + m1.matrix[5] * m2.matrix[5] + m1.matrix[9] * m2.matrix[6] + m1.matrix[13] * m2.matrix[7];
	result.matrix[9] = m1.matrix[1] * m2.matrix[8] + m1.matrix[5] * m2.matrix[9] + m1.matrix[9] * m2.matrix[10] + m1.matrix[13] * m2.matrix[11];
	result.matrix[13] = m1.matrix[1] * m2.matrix[12] + m1.matrix[5] * m2.matrix[13] + m1.matrix[9] * m2.matrix[14] + m1.matrix[13] * m2.matrix[15];
	result.matrix[2] = m1.matrix[2] * m2.matrix[0] + m1.matrix[6] * m2.matrix[1] + m1.matrix[10] * m2.matrix[2] + m1.matrix[14] * m2.matrix[3];
	result.matrix[6] = m1.matrix[2] * m2.matrix[4] + m1.matrix[6] * m2.matrix[5] + m1.matrix[10] * m2.matrix[6] + m1.matrix[14] * m2.matrix[7];
	result.matrix[10] = m1.matrix[2] * m2.matrix[8] + m1.matrix[6] * m2.matrix[9] + m1.matrix[10] * m2.matrix[10] + m1.matrix[14] * m2.matrix[11];
	result.matrix[14] = m1.matrix[2] * m2.matrix[12] + m1.matrix[6] * m2.matrix[13] + m1.matrix[10] * m2.matrix[14] + m1.matrix[14] * m2.matrix[15];
	result.matrix[3] = m1.matrix[3] * m2.matrix[0] + m1.matrix[7] * m2.matrix[1] + m1.matrix[11] * m2.matrix[2] + m1.matrix[15] * m2.matrix[3];
	result.matrix[7] = m1.matrix[3] * m2.matrix[4] + m1.matrix[7] * m2.matrix[5] + m1.matrix[11] * m2.matrix[6] + m1.matrix[15] * m2.matrix[7];
	result.matrix[11] = m1.matrix[3] * m2.matrix[8] + m1.matrix[7] * m2.matrix[9] + m1.matrix[11] * m2.matrix[10] + m1.matrix[15] * m2.matrix[11];
	result.matrix[15] = m1.matrix[2] * m2.matrix[12] + m1.matrix[7] * m2.matrix[13] + m1.matrix[11] * m2.matrix[14] + m1.matrix[15] * m2.matrix[15];

	return result;

}

mat4 mat4::inverse(const mat4& m)
{
	double b[16], det;
	mat4 m_inv;

	b[0] =
		m.matrix[5] * m.matrix[10] * m.matrix[15] -
		m.matrix[5] * m.matrix[11] * m.matrix[14] -
		m.matrix[9] * m.matrix[6] * m.matrix[15] +
		m.matrix[9] * m.matrix[7] * m.matrix[14] +
		m.matrix[13] * m.matrix[6] * m.matrix[11] -
		m.matrix[13] * m.matrix[7] * m.matrix[10];

	b[4] =
		-m.matrix[4] * m.matrix[10] * m.matrix[15] +
		m.matrix[4] * m.matrix[11] * m.matrix[14] +
		m.matrix[8] * m.matrix[6] * m.matrix[15] -
		m.matrix[8] * m.matrix[7] * m.matrix[14] -
		m.matrix[12] * m.matrix[6] * m.matrix[11] +
		m.matrix[12] * m.matrix[7] * m.matrix[10];

	b[8] =
		m.matrix[4] * m.matrix[9] * m.matrix[15] -
		m.matrix[4] * m.matrix[11] * m.matrix[13] -
		m.matrix[8] * m.matrix[5] * m.matrix[15] +
		m.matrix[8] * m.matrix[7] * m.matrix[13] +
		m.matrix[12] * m.matrix[5] * m.matrix[11] -
		m.matrix[12] * m.matrix[7] * m.matrix[9];

	b[12] =
		-m.matrix[4] * m.matrix[9] * m.matrix[14] +
		m.matrix[4] * m.matrix[10] * m.matrix[13] +
		m.matrix[8] * m.matrix[5] * m.matrix[14] -
		m.matrix[8] * m.matrix[6] * m.matrix[13] -
		m.matrix[12] * m.matrix[5] * m.matrix[10] +
		m.matrix[12] * m.matrix[6] * m.matrix[9];

	b[1] =
		-m.matrix[1] * m.matrix[10] * m.matrix[15] +
		m.matrix[1] * m.matrix[11] * m.matrix[14] +
		m.matrix[9] * m.matrix[2] * m.matrix[15] -
		m.matrix[9] * m.matrix[3] * m.matrix[14] -
		m.matrix[13] * m.matrix[2] * m.matrix[11] +
		m.matrix[13] * m.matrix[3] * m.matrix[10];

	b[5] =
		m.matrix[0] * m.matrix[10] * m.matrix[15] -
		m.matrix[0] * m.matrix[11] * m.matrix[14] -
		m.matrix[8] * m.matrix[2] * m.matrix[15] +
		m.matrix[8] * m.matrix[3] * m.matrix[14] +
		m.matrix[12] * m.matrix[2] * m.matrix[11] -
		m.matrix[12] * m.matrix[3] * m.matrix[10];

	b[9] =
		-m.matrix[0] * m.matrix[9] * m.matrix[15] +
		m.matrix[0] * m.matrix[11] * m.matrix[13] +
		m.matrix[8] * m.matrix[1] * m.matrix[15] -
		m.matrix[8] * m.matrix[3] * m.matrix[13] -
		m.matrix[12] * m.matrix[1] * m.matrix[11] +
		m.matrix[12] * m.matrix[3] * m.matrix[9];

	b[13] =
		m.matrix[0] * m.matrix[9] * m.matrix[14] -
		m.matrix[0] * m.matrix[10] * m.matrix[13] -
		m.matrix[8] * m.matrix[1] * m.matrix[14] +
		m.matrix[8] * m.matrix[2] * m.matrix[13] +
		m.matrix[12] * m.matrix[1] * m.matrix[10] -
		m.matrix[12] * m.matrix[2] * m.matrix[9];

	b[2] =
		m.matrix[1] * m.matrix[6] * m.matrix[15] -
		m.matrix[1] * m.matrix[7] * m.matrix[14] -
		m.matrix[5] * m.matrix[2] * m.matrix[15] +
		m.matrix[5] * m.matrix[3] * m.matrix[14] +
		m.matrix[13] * m.matrix[2] * m.matrix[7] -
		m.matrix[13] * m.matrix[3] * m.matrix[6];

	b[6] =
		-m.matrix[0] * m.matrix[6] * m.matrix[15] +
		m.matrix[0] * m.matrix[7] * m.matrix[14] +
		m.matrix[4] * m.matrix[2] * m.matrix[15] -
		m.matrix[4] * m.matrix[3] * m.matrix[14] -
		m.matrix[12] * m.matrix[2] * m.matrix[7] +
		m.matrix[12] * m.matrix[3] * m.matrix[6];

	b[10] =
		m.matrix[0] * m.matrix[5] * m.matrix[15] -
		m.matrix[0] * m.matrix[7] * m.matrix[13] -
		m.matrix[4] * m.matrix[1] * m.matrix[15] +
		m.matrix[4] * m.matrix[3] * m.matrix[13] +
		m.matrix[12] * m.matrix[1] * m.matrix[7] -
		m.matrix[12] * m.matrix[3] * m.matrix[5];

	b[14] =
		-m.matrix[0] * m.matrix[5] * m.matrix[14] +
		m.matrix[0] * m.matrix[6] * m.matrix[13] +
		m.matrix[4] * m.matrix[1] * m.matrix[14] -
		m.matrix[4] * m.matrix[2] * m.matrix[13] -
		m.matrix[12] * m.matrix[1] * m.matrix[6] +
		m.matrix[12] * m.matrix[2] * m.matrix[5];

	b[3] =
		-m.matrix[1] * m.matrix[6] * m.matrix[11] +
		m.matrix[1] * m.matrix[7] * m.matrix[10] +
		m.matrix[5] * m.matrix[2] * m.matrix[11] -
		m.matrix[5] * m.matrix[3] * m.matrix[10] -
		m.matrix[9] * m.matrix[2] * m.matrix[7] +
		m.matrix[9] * m.matrix[3] * m.matrix[6];

	b[7] =
		m.matrix[0] * m.matrix[6] * m.matrix[11] -
		m.matrix[0] * m.matrix[7] * m.matrix[10] -
		m.matrix[4] * m.matrix[2] * m.matrix[11] +
		m.matrix[4] * m.matrix[3] * m.matrix[10] +
		m.matrix[8] * m.matrix[2] * m.matrix[7] -
		m.matrix[8] * m.matrix[3] * m.matrix[6];

	b[11] =
		-m.matrix[0] * m.matrix[5] * m.matrix[11] +
		m.matrix[0] * m.matrix[7] * m.matrix[9] +
		m.matrix[4] * m.matrix[1] * m.matrix[11] -
		m.matrix[4] * m.matrix[3] * m.matrix[9] -
		m.matrix[8] * m.matrix[1] * m.matrix[7] +
		m.matrix[8] * m.matrix[3] * m.matrix[5];

	b[15] =
		m.matrix[0] * m.matrix[5] * m.matrix[10] -
		m.matrix[0] * m.matrix[6] * m.matrix[9] -
		m.matrix[4] * m.matrix[1] * m.matrix[10] +
		m.matrix[4] * m.matrix[2] * m.matrix[9] +
		m.matrix[8] * m.matrix[1] * m.matrix[6] -
		m.matrix[8] * m.matrix[2] * m.matrix[5];

	det = m.matrix[0] * b[0] + m.matrix[1] * b[4] + m.matrix[2] * b[8] + m.matrix[3] * b[12];

	if (det == 0) return m_inv;

	det = 1.0 / det;

	for (int i = 0; i < 16; i++)
		m_inv.matrix[i] = b[i] * det;

	return m_inv;
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