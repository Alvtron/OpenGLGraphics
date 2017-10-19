#pragma once
#include "Shader.h"

class ObjectShader :
	public Shader
{
public:
	ObjectShader();
	ObjectShader(const char * vertexPath, const char * fragmentPath, const char * geometryPath = nullptr);
	~ObjectShader();
};