#include "CubeMapShader.h"



CubeMapShader::CubeMapShader()
{
}

CubeMapShader::CubeMapShader(const char * vertexPath, const char * fragmentPath, const char * geometryPath)
	: Shader(vertexPath, fragmentPath, geometryPath)
{
	this->use();
	this->setInt("skybox", 0);
}


CubeMapShader::~CubeMapShader()
{
}
