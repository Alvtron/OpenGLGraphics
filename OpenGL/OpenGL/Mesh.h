#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Shader.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "Texture.h"
#include "Maths.h"

class Mesh
{
private:
	static const std::vector<float> EMPTY_FLOAT_VECTOR;
	static const std::vector<unsigned int> EMPTY_UINT_VECTOR;
	unsigned int VBO, VAO, EBO;
	static unsigned int num_meshes;
	bool hasVertices = false, hasNormals = false, hasColors = false, hasTextures = false, hasIndices = false;
	bool storedOnGPU = false;
	std::vector<float> vertex_data;
	std::vector<unsigned int> indices;
	GLenum draw_mode = GL_TRIANGLES;
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
	bool createVertexData(const std::vector<vec3>& vertices, const std::vector<vec3>& normals, const std::vector<vec3>& colors, const std::vector<vec2>& textures, const std::vector<unsigned int>& indices);
	bool createVertexData(const std::vector<vec3>& vertices, const std::vector<vec3>& normals, const std::vector<vec3>& colors, const std::vector<vec2>& textures);
	bool addVertexData(const std::vector<vec3>& data, VERTEX_DATA_TYPE data_type);
	bool addIndices(const std::vector<unsigned int>& indices);
	bool storeOnGPU();
	bool setDrawMode(GLenum mode);
	bool drawObject(const Shader * shader, vec3 position, vec3 scale_vector, float rotation_degrees, vec3 rotation_vector, Texture texture, int from_index, int to_index);
	bool drawObject(const Shader * shader, vec3 position, vec3 scale_vector, float rotation_degrees, vec3 rotation_vector, const Texture texture);
	bool drawObject(const Shader * shader, vec3 position, float rotation_degrees, vec3 rotation_vector, const Texture texture);
	bool drawObject(const Shader * shader, vec3 position, vec3 scale_vector, const Texture texture);
	bool drawObject(const Shader * shader, vec3 position, const Texture texture);
	bool drawObject(const Shader * shader, const Texture texture);
	bool deAllocate();
	unsigned int stride();
	unsigned int verticeStride();
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