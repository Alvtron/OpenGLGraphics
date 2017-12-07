#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "maths.h"
#include "Shader.h"
#include "Material.h"
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
	/* Private function: Split up vec3 data into smaller pieces */
	std::vector<vec3> subdivide(const std::vector<vec3> & vertex_data);
	/* Private function: Split up vec2 data into smaller pieces */
	std::vector<vec2> subdivide(const std::vector<vec2> & vertex_data);
protected:
	/* Set draw mode. Defaults to GL_TRIANGLES */
	void setDrawMode(GLenum mode);
public:
	std::vector<vec3> vertices, normals, colors, tangents, bitangents;
	std::vector<vec2> uvs;
	std::vector<unsigned int> indices;

	/* Cosntructor */
	Vertex(const std::vector<vec3> &vertices = std::vector<vec3>(), const std::vector<vec3> &normal = std::vector<vec3>(), const std::vector<vec3> &color = std::vector<vec3>(), const std::vector<vec2> &uv = std::vector<vec2>(), const std::vector<vec3> &tangent = std::vector<vec3>(), const std::vector<vec3>& bitangents = std::vector<vec3>(), const std::vector<unsigned int>& indices = std::vector<unsigned int>());
	/* De-constructor */
	~Vertex();

	/* Set scale (creates scale model) */
	void setScale(const vec3 &scale_vector);
	/* Returns scale model */
	mat4& getScale();
	/* Returns UV scale */
	vec2& getUVScale();
	/* Set rotation (creates rotation model) */
	void setRotate(const float & rotate_degrees, const vec3 & rotate_vector);
	/* Returns rotation model */
	mat4& getRotation();
	/* Set position (create translation model) */
	void setPosition(const vec3 &position_vector);
	/* Returns translation model */
	mat4& getPosition();

	/* Returns the size of the vertex data (per stride)*/
	const unsigned int size();
	/* Returns the number of floats */
	const unsigned int dataSize();

	/* Returns wheter this vertex has vertices or not */
	bool hasVertices();
	/* Returns wheter this vertex has normals or not */
	bool hasNormals();
	/* Returns wheter this vertex has colors or not */
	bool hasColors();
	/* Returns wheter this vertex has uvs or not */
	bool hasUVs();
	/* Returns wheter this vertex has tangents or not */
	bool hasTangents();
	/* Returns wheter this vertex has bitangents or not */
	bool hasBitangents();
	/* Returns wheter this vertex has indices or not */
	bool hasIndices();

	/* Returns the stride (size of the raw data per float)*/
	const unsigned int stride();
	/* Returns the stride in vertex data*/
	const unsigned int verticeStride();
	/* Returns the first index of the first normal in the vertex data. */
	const unsigned int normalStride();
	/* Returns the first index of the first color in the vertex data. */
	const unsigned int colorStride();
	/* Returns the first index of the first texture in the vertex data. */
	const unsigned int uvStride();
	/* Returns the first index of the first tangent in the vertex data. */
	const unsigned int tangentStride();
	/* Returns the first index of the first bitangent in the vertex data. */
	const unsigned int bitangentStride();

	/* Generate buffers and store vertex data on the GPU. Call drawObject(...) to draw it */
	bool storeOnGPU();
	/* Set if textures should scale with object or not. False by default. */
	void scaleTextures(const bool ENABLE);
	/* Draw vertex data from GPU */
	bool drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, const float &rotation_degrees, const vec3 &rotation_vector, Material *texture = nullptr);
	/* Draw vertex data from GPU */
	bool drawObject(const Shader * shader, const vec3 &position, const float &rotation_degrees, const vec3 &rotation_vector, Material *texture = nullptr);
	/* Draw vertex data from GPU */
	bool drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, Material *texture = nullptr);
	/* Draw vertex data from GPU */
	bool drawObject(const Shader * shader, const vec3 &position, Material *texture = nullptr);
	/* Draw vertex data from GPU */
	bool drawObject(const Shader * shader, Material *texture = nullptr);
	/* De-allocate vertex data once it has outlived it's purpose */
	bool deAllocate();

	/* Prints all vertices in a human-readable format */
	const void printVertices();
	/* Prints all normals in a human-readable format */
	const void printNormals();
	/* Prints all colors in a human-readable format */
	const void printColors();
	/* Prints all uvs in a human-readable format */
	const void printUVs();
	/* Prints all tangents in a human-readable format */
	const void printTangents();
	/* Prints all bitangents in a human-readable format */
	const void printBitangents();
	/* Prints all indices in a human-readable format */
	const void printIndices();
	/* Prints vertex data in a human-readable format */
	const void printVertexData();
	/* Prints vertex data sizes in a human-readable format */
	const void printDataSizes();

	/* Return the combined vertex data */
	std::vector<float> data();
	/* Calculate the normals of each triangle, https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal */
	void createNormals();
	/* Set color of on all vertices */
	void setColor(const vec3 & color = vec3(1.0f, 1.0f, 1.0f));
	/* Calculate tangent vectors for all triangles */
	void calculateTangents();
	/* Unwrap vertex data with indices. */
	std::vector<vec3> unwrap(const std::vector<vec3>& vertex_data);
	/* Unwrap vertex data with indices. */
	std::vector<vec2> unwrap(const std::vector<vec2>& vertex_data);
	/* Split up mesh into smaller pieces. Keep @param divitions below 10 */
	void subdivide(const unsigned int & divitions);
};