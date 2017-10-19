#pragma once
#include "Shader.h"
class CubeMapShader : public Shader
{
public:
	CubeMapShader();
	CubeMapShader(const char * vertexPath, const char * fragmentPath, const char * geometryPath = nullptr);
	~CubeMapShader();
};