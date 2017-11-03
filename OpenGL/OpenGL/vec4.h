#pragma once

#include <iostream>

class vec4 {

public:
	float x;
	float y;
	float z;
	float w;

	vec4();
	vec4(const float& a, const float& b, const float& c, const float& d);
	vec4(const float& a, const float& b, const float& c);

	/**
		Multiplies a vector with a matrix
	@param m The left matrix.
	@param v The right vector.
	@return The product of m and v, which is a vec4
	*/
	static vec4 multiply(const mat4& m, const vec4& v);

	/**
		Calculates the cross product between two vectors
	@param v1 Vector 1.
	@param v2 Vector 2.
	@return The cross product of v1 and v2, which is a new vector
	*/
	static vec4 cross(const vec4& v1, const vec4& v2);

	/**
		Calculates the dot product between two vectors
	@param v1 Vector 1.
	@param v2 Vector 2.
	@return The dot product of v1 and v2, which is a number
	*/
	static float dot(const vec4& v1, const vec4& v2);

	/**
		Normalizes the vector v
	@param v The vector to be normalized.
	@return The normalized vector v
	*/
	static vec4 normalize(const vec4& v);

	/**
		Scales a vector by a scalar k
	@param v The vector to be scaled.
	@param k The scalar.
	@return The scaled vector v
	*/
	static vec4 scale(const vec4& v, const float& k);

	/**
		Arithmetic operations on vectors
	@param v1 Vector 1.
	@param v2 Vector 2.
	@return The resulting vector of the arithmetic operation
	*/
	static vec4 add(const vec4& v1, const vec4& v2);
	static vec4 subtract(const vec4& v1, const vec4& v2);
	static vec4 multiply(const vec4& v1, const vec4& v2);
	static vec4 divide(const vec4& v1, const vec4& v2);

	/**
		These methods overwrites the arithmetic operators when they are used between two vec4 objects 
	@param v1 Vector 1.
	@param v2 Vector 2.
	@return The resulting vector of the arithmetic operation
	*/
	friend vec4 operator+(const vec4& left, const vec4& right);
	friend vec4 operator-(const vec4& left, const vec4& right);
	friend vec4 operator*(const vec4& left, const vec4& right);
	friend vec4 operator*(const mat4& left, const vec4& right);
	friend vec4 operator/(const vec4& left, const vec4& right);

	/**
		A custom way of printing out a vec4 object to the console
	*/
	friend std::ostream& operator<<(std::ostream& stream, const vec4& v);

}; 