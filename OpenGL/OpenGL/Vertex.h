#pragma once
#include "maths.h"
#include <string>
#include <vector>

class Vertex
{
private:
public:
	std::vector<vec3> vertices, normals, colors, tangents, bitangents;
	std::vector<vec2> uvs;
	std::vector<unsigned int> indices;

	Vertex(const std::vector<vec3> &vertices = std::vector<vec3>(), const std::vector<vec3> &normal = std::vector<vec3>(), const std::vector<vec3> &color = std::vector<vec3>(), const std::vector<vec2> &uv = std::vector<vec2>(), const std::vector<vec3> &tangent = std::vector<vec3>(), const std::vector<vec3>& bitangents = std::vector<vec3>(), const std::vector<unsigned int>& indices = std::vector<unsigned int>());
	~Vertex();

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

	const void printVertices();
	const void printNormals();
	const void printColors();
	const void printUVs();
	const void printTangents();
	const void printBitangents();
	const void printIndices();
	const void printVertexData();

	std::vector<float> combinedVertexData();
};