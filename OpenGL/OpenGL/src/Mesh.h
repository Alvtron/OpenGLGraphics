#ifndef MESH_HEADER
#define MESH_HEADER

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <cmath>
#include "shader.h"
#include <iostream>
#include <iomanip>
#include <vector>

class Mesh
{
private:
	unsigned int VBO, VAO, EBO;
	static unsigned int num_meshes;
protected:
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> colors;
	std::vector<float> textures;
	std::vector<unsigned int> indices;
public:
	Mesh();
	~Mesh();
	void storeOnGPU();
	void drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, unsigned int texture_diffuse, unsigned int texture_specular);
	void drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, unsigned int texture_diffuse, unsigned int texture_specular);
	void deAllocate();
	void printVertices();
};

#endif