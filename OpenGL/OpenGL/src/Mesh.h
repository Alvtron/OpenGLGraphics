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
	std::vector<float> vertex_data;
	std::vector<unsigned int> indices;
public:
	Mesh();
	~Mesh();
	void createVertexData(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<float>& colors, const std::vector<float>& textures, const std::vector<unsigned int>& indices);
	void storeOnGPU();
	void drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, unsigned int texture_diffuse, unsigned int texture_specular);
	void drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, unsigned int texture_diffuse, unsigned int texture_specular);
	void deAllocate();
	void printVertices();
	void printNormals();
	void printColors();
	void printTextures();
	void printIndices();
	void printVertexData();
};

#endif