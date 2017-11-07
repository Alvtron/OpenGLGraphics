#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Maths.h"
#include "MeshUtility.h"
#include "Vertex.h"

class Mesh
{
private:
	unsigned int VBO, VAO, EBO;
	bool storedOnGPU = false, scaleTexture = false;
	GLenum draw_mode = GL_TRIANGLES;
protected:
	Vertex vertex;
	void setDrawMode(GLenum mode);
public:
	Mesh();
	~Mesh();
	bool storeOnGPU();
	void scaleTextures(const bool ENABLE);
	bool drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, const float &rotation_degrees, const vec3 &rotation_vector, Texture &texture, const int &from_index, const int &to_index);
	bool drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, const float &rotation_degrees, const vec3 &rotation_vector, Texture &texture);
	bool drawObject(const Shader * shader, const vec3 &position, const float &rotation_degrees, const vec3 &rotation_vector, Texture &texture);
	bool drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, Texture &texture);
	bool drawObject(const Shader * shader, const vec3 &position, Texture &texture);
	bool drawObject(const Shader * shader, Texture &texture);
	bool deAllocate();
};