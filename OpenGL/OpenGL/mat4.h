#pragma once

#include <iostream>
#include "Vec3.h"

class mat4 {

public:
	float matrix[16];

	mat4();

	/**
		Constructs a 4x4 identity matrix
	@return An identity matrix
	*/
	static mat4 makeIdentity();

	/**
		Constructs a 4x4 scale matrix that can be used to scale a vector by multiplication
	@param scale A vec3 which describes how much you want to scale a point in x, y and z directions.
	@return A scale matrix 
	*/
	static mat4 makeScale(const vec3& scale);

	/**
		Constructs a 4x4 rotation matrix that can be used to rotate a vector by multiplication
	@param angle A float which describes how far you want to rotate around the given axis in degrees (NOT RADIANS).
	@param axis A vec3 which describes how you want to rotate a point around the x, y and z axis.
	@return A rotation matrix
	*/
	static mat4 makeRotate(const float& angle, const vec3& axis);

	/**
		Constructs a 4x4 translation matrix that can be used to translate a vector by multiplication
	@param translation A vec3 which describes how much you want to move a point in the x, y and z directions.
	@return A translation matrix
	*/
	static mat4 makeTranslate(const vec3& translation);

	/**
		Constructs a 4x4 perspective projection matrix that we will use to define our projection in the world
	@param angle Specifying the field of view in degrees (NOT RADIANS).
	@param aspectRatio Specifying the correlation between screenwidth and screenheight.
	@param near Specifying the near plane of the world (objects rendered in front of the near plane will not be visible).
	@param far Specifying the far plane of the world (objects rendered behind the far plane will not be visible).
	@return A perspective projection matrix
	*/
	static mat4 makePerspective(const float& angle, const float& aspectRatio, const float& near, const float& far);

	/**
		Constructs a 4x4 orthographic projection matrix that we will use to define our projection in the xy-plane
	@param l Specifying the left side of the screen.
	@param r Specifying the right side of the screen.
	@param b Specifying the bottom of the screen.
	@param t Specifying the top of the screen.
	@return An orthographic projection matrix
	*/
	static mat4 makeOrtho(const float& l, const float& r, const float& b, const float& t);

	/**
		Removes the translation from a 4x4 matrix
	@param m A 4x4 matrix we will remove the translation vector from.
	@return A 4x4 matrix without the translation attribute
	*/
	static mat4 removeTranslation(const mat4& m);

	/**
		Multiplies two 4x4 matrices together
	@param m1 The left 4x4 matrix.
	@param m2 The right 4x4 matrix.
	@return The product of m1 and m2
	*/
	static mat4 multiply(const mat4& m1, const mat4& m2);

	/**
		Inverste a 4x4 matrix
		@param m - a 4x4 matrix tto be inversed
		@return the inverted matrix
	*/
	static mat4 inverse(const mat4 & m);

	/**
		This method overwrites the "*" operator, when used between two mat4 objects
	@param left The left 4x4 matrix.
	@param right The right 4x4 matrix.
	@return The product of left and right
	*/
	friend mat4 operator*(const mat4& left, const mat4& right);

	/**
		A custom way of printing out a mat4 object to the console
	*/
	friend std::ostream& operator<<(std::ostream& stream, const mat4& m);

};