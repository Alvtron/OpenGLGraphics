#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Maths.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	void checkCompileErrors(GLuint shader, std::string type);
public:
	unsigned int ID;
	Shader();
	Shader(const char * vertexPath, const char * fragmentPath, const char * geometryPath = nullptr);
	void use();
	void setBool(const std::string & name, bool value) const;
	void setInt(const std::string & name, int value) const;
	void setFloat(const std::string & name, float value) const;
	void setVec2(const std::string & name, const vec2 & value) const;
	void setVec2(const std::string & name, float x, float y) const;
	void setVec3(const std::string & name, const vec3 & value) const;
	void setVec3(const std::string & name, float x, float y, float z) const;
	void setVec4(const std::string & name, const vec4 & value) const;
	void setVec4(const std::string & name, float x, float y, float z, float w);
	void setMat2(const std::string & name, const mat2 & mat) const;
	void setMat3(const std::string & name, const mat3 & mat) const;
	void setMat4(const std::string & name, const mat4 & mat) const;
};