#include "LightShader.h"

/* Default constructor */
LightShader::LightShader()
{
}

/* Load shader from GLSL code store in file. Specify filepath to Vertex Shader and Fragment Shader, and Geometry Shader (unrequired). Specify a color for the object as well.  */
LightShader::LightShader(const char * vertexPath, const char * fragmentPath, const char * geometryPath, glm::vec3 light_color)
	: Shader(vertexPath, fragmentPath, geometryPath)
{
	this->use();
	this->setVec3("lightColor", light_color);
	this->setBool("hasLightColor", true);
}

/* Load shader from GLSL code store in file. Specify filepath to Vertex Shader and Fragment Shader. Specify a color for the object as well.  */
LightShader::LightShader(const char * vertexPath, const char * fragmentPath, glm::vec3 light_color)
	: Shader(vertexPath, fragmentPath)
{
	this->use();
	this->setVec3("lightColor", light_color);
	this->setBool("hasLightColor", true);
}

/* De-constructor */
LightShader::~LightShader()
{
}

/* Set light object color */
void LightShader::SetLightColor(glm::vec3 light_color)
{
	this->use();
	this->setVec3("lightColor", light_color);
	this->setBool("hasLightColor", true);
}