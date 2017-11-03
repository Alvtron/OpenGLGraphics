#pragma once
#include "Shader.h"

class LightShader : public Shader
{
public:
	LightShader();
	LightShader(const char * vertexPath, const char * fragmentPath, const char * geometryPath = nullptr, vec3 light_color = vec3(1.0f, 1.0f, 1.0f));
	LightShader(const char * vertexPath, const char * fragmentPath, vec3 light_color = vec3(1.0f, 1.0f, 1.0f));
	~LightShader();
	void SetLightColor(vec3 light_color);
};