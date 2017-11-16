#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "maths.h"
#include "Shader.h"
#include "Texture.h"
#include "Maths.h"

class Vertex
{
private:
	mat4 scale = mat4::makeIdentity(), rotate = mat4::makeIdentity(), position = mat4::makeIdentity();
	vec2 uv_scale = vec2(1.0f, 1.0f);
	unsigned int VBO, VAO, EBO;
	bool storedOnGPU = false, scaleTexture = false;
	GLenum draw_mode = GL_TRIANGLES;
	std::vector<vec3> subdivide(const std::vector<vec3> & vertex_data);
	std::vector<vec2> subdivide(const std::vector<vec2> & vertex_data);
protected:
	void setDrawMode(GLenum mode);
public:
	std::vector<vec3> vertices, normals, colors, tangents, bitangents;
	std::vector<vec2> uvs;
	std::vector<unsigned int> indices;

	Vertex(const std::vector<vec3> &vertices = std::vector<vec3>(), const std::vector<vec3> &normal = std::vector<vec3>(), const std::vector<vec3> &color = std::vector<vec3>(), const std::vector<vec2> &uv = std::vector<vec2>(), const std::vector<vec3> &tangent = std::vector<vec3>(), const std::vector<vec3>& bitangents = std::vector<vec3>(), const std::vector<unsigned int>& indices = std::vector<unsigned int>());
	~Vertex();

	void setScale(const vec3 &scale_vector);
	mat4& getScale();
	vec2& getUVScale();
	void setRotate(const float & rotate_degrees, const vec3 & rotate_vector);
	mat4& getRotation();
	void setPosition(const vec3 &position_vector);
	mat4& getPosition();

	const unsigned int size();
	const unsigned int dataSize();

	bool hasVertices();
	bool hasNormals();
	bool hasColors();
	bool hasUVs();
	bool hasTangents();
	bool hasBitangents();
	bool hasIndices();

	const unsigned int stride();
	const unsigned int verticeStride();
	const unsigned int normalStride();
	const unsigned int colorStride();
	const unsigned int uvStride();
	const unsigned int tangentStride();
	const unsigned int bitangentStride();

	bool storeOnGPU();
	void scaleTextures(const bool ENABLE);
	bool drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, const float &rotation_degrees, const vec3 &rotation_vector, Texture &texture);
	bool drawObject(const Shader * shader, const vec3 &position, const float &rotation_degrees, const vec3 &rotation_vector, Texture &texture);
	bool drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, Texture &texture);
	bool drawObject(const Shader * shader, const vec3 &position, Texture &texture);
	bool drawObject(const Shader * shader, Texture &texture);
	bool deAllocate();

	const void printVertices();
	const void printNormals();
	const void printColors();
	const void printUVs();
	const void printTangents();
	const void printBitangents();
	const void printIndices();
	const void printVertexData();

	const void printDataSizes();

	std::vector<float> data();
	void createNormals();
	void createColors(const vec3 & color = vec3(1.0f, 1.0f, 1.0f));
	void calculateTangents();
	std::vector<vec3> unwrap(const std::vector<vec3>& vertex_data);
	std::vector<vec2> unwrap(const std::vector<vec2>& vertex_data);

	void subdivide(const unsigned int & divitions);
};