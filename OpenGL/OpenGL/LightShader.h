#pragma once
#include "Shader.h"

class LightShader : public Shader
{
public:
	LightShader();
	LightShader(const char * vertexPath, const char * fragmentPath, const char * geometryPath = nullptr, glm::vec3 light_color = glm::vec3(1.0f));
	LightShader(const char * vertexPath, const char * fragmentPath, glm::vec3 light_color = glm::vec3(1.0f));
	~LightShader();
	void SetLightColor(glm::vec3 light_color);
};