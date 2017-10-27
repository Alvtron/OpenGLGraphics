#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <cmath>
#include "Shader.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "Texture.h"

class Mesh
{
private:
	static const std::vector<float> EMPTY_FLOAT_VECTOR;
	static const std::vector<unsigned int> EMPTY_UINT_VECTOR;
	unsigned int VBO, VAO, EBO;
	static unsigned int num_meshes;
	bool hasVertices = false, hasNormals = false, hasColors = false, hasTextures = false, hasIndices = false;
	std::vector<float> vertex_data;
	std::vector<unsigned int> indices;
public:
	enum VERTEX_DATA_TYPE : char {
		MESH_VERTICE = 'V',
		MESH_NORMAL = 'N',
		MESH_COLOR = 'C',
		MESH_TEXTURE = 'T',
		MESH_INDICE = 'I'
	};
	Mesh();
	~Mesh();
	void createVertexData(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<float>& colors, const std::vector<float>& textures, const std::vector<unsigned int>& indices);
	void addVertexData(const std::vector<float>& vertices, VERTEX_DATA_TYPE data_type);
	void addIndices(const std::vector<unsigned int>& indices);
	void storeOnGPU();
	void drawObject(const Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, Texture texture, int from_index, int to_index);
	void drawObject(const Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, const Texture texture);
	void drawObject(const Shader * shader, glm::vec3 position, float rotation_degrees, glm::vec3 rotation_vector, const Texture texture);
	void drawObject(const Shader * shader, glm::vec3 position, glm::vec3 scale_vector, const Texture texture);
	void drawObject(const Shader * shader, glm::vec3 position, const Texture texture);
	void drawObject(const Shader * shader, const Texture texture);
	void deAllocate();
	unsigned int stride();
	unsigned int VerticeStride();
	unsigned int normalStride();
	unsigned int colorStride();
	unsigned int textureStride();
	void printVertices();
	void printNormals();
	void printColors();
	void printTextures();
	void printIndices();
	void printVertexData();
};