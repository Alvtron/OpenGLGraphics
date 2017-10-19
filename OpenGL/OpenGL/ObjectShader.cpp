#include "ObjectShader.h"

/* Default constructor */
ObjectShader::ObjectShader()
{
}

/* Load shader from GLSL code store in file. Specify filepath to Vertex Shader and Fragment Shader, and Geometry Shader (unrequired). */
ObjectShader::ObjectShader(const char * vertexPath, const char * fragmentPath, const char * geometryPath)
	: Shader(vertexPath, fragmentPath, geometryPath)
{
	this->use();
	this->setInt("material.diffuse", 0);
	this->setInt("material.specular", 1);
	this->setInt("material.normal", 2);
	this->setInt("material.displacement", 3);
	this->setInt("material.ao", 4);
}

/* De-constructor */
ObjectShader::~ObjectShader()
{
}