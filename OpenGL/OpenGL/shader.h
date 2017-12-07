#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include "GL/glew.h"
#include "gtc/type_ptr.hpp"
#include "maths.h"
#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

class Shader {
public:
	unsigned int vertex_shader;
	unsigned int fragment_shader;
	unsigned int ID;
	char vertex_path[256];
	char fragment_path[256];
	/* Read from file specified and store in a string */
	static char * readFile(const char * file_path);
	/* Initialize vertex and fragment shader. Read the files and compile them. Create shader program. */
	int init(const char* vertex_shader_path, const char* fragment_shader_path);
	/* Use this program */
	void use();
	/* Set uniform: bool */
	void setBool(const char*, bool value) const;
	/* Set uniform: bool */
	void setBool(std::string name, bool value) const;
	/* Set uniform: int */
	void setInt(const char*, int value) const;
	/* Set uniform: int */
	void setInt(std::string name, int value) const;
	/* Set uniform: float */
	void setFloat(const char*, float value) const;
	/* Set uniform: float */
	void setFloat(std::string name, float value) const;
	/* Set uniform: vec2 */
	void setVec2(const char*, const vec2 & value) const;
	/* Set uniform: vec2 */
	void setVec2(std::string name, const vec2 & value) const;
	/* Set uniform: vec2 */
	void setVec2(const char*, float x, float y) const;
	/* Set uniform: vec2 */
	void setVec3(const char*, const vec3 & value) const;
	/* Set uniform: vec3 */
	void setVec3(std::string name, const vec3 & value) const;
	/* Set uniform: vec3 */
	void setVec3(const char*, float x, float y, float z) const;
	/* Set uniform: vec3 */
	void setVec4(const char*, const vec4 & value) const;
	/* Set uniform: vec4 */
	void setVec4(std::string name, const vec4 & value) const;
	/* Set uniform: vec4 */
	void setVec4(const char*, float x, float y, float z, float w);
	/* Set uniform: mat2 */
	void setMat2(const char*, const mat2 & mat) const;
	/* Set uniform: mat2 */
	void setMat2(std::string, const mat2 & mat) const;
	/* Set uniform: mat3 */
	void setMat3(const char*, const mat3 & mat) const;
	/* Set uniform: mat3 */
	void setMat3(std::string name, const mat3 & mat) const;
	/* Set uniform: mat4  */
	void setMat4(const char*, const mat4 & mat) const;
	/* Set uniform: mat4 */
	void setMat4(std::string name, const mat4 & mat) const;
	/* Set Texture 1D  */
	void setTexture1D(Texture t, const char* name);
	/* Set Texture 2D  */
	void setTexture2D(Texture t, const char* name);
	/* Set Texture 3D  */
	void setTexture3D(Texture t, const char* name);
};
