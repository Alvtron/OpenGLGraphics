#include "Vertex.h"

Vertex::Vertex(const std::vector<vec3>& vertices, const std::vector<vec3>& normals, const std::vector<vec3>& colors, const std::vector<vec2>& uvs, const std::vector<vec3>& tangents, const std::vector<vec3>& bitangents, const std::vector<unsigned int>& indices)
{
	this->vertices = vertices;
	this->normals = normals;
	this->colors = colors;
	this->uvs = uvs;
	this->tangents = tangents;
	this->bitangents = bitangents;
	this->indices = indices;
}

/* De-constructor */
Vertex::~Vertex()
{
}

/* Returns the size of the vertex data (per stride)*/
const unsigned int Vertex::size()
{
	return dataSize() / stride();
}

/* Returns the number of floats */
const unsigned int Vertex::dataSize()
{
	return vertices.size() * 3 + normals.size() * 3 + colors.size() * 3 + uvs.size() * 2 + tangents.size() * 3;
}

/* Returns wheter this vertex has vertices or not */
bool Vertex::hasVertices()
{
	return (vertices.size() > 0);
}

/* Returns wheter this vertex has normals or not */
bool Vertex::hasNormals()
{
	return (normals.size() > 0);
}

/* Returns wheter this vertex has colors or not */
bool Vertex::hasColors()
{
	return (colors.size() > 0);
}

/* Returns wheter this vertex has uvs or not */
bool Vertex::hasUVs()
{
	return (uvs.size() > 0);
}

/* Returns wheter this vertex has tangents or not */
bool Vertex::hasTangents()
{
	return (tangents.size() > 0);
}

/* Returns wheter this vertex has bitangents or not */
bool Vertex::hasBitangents()
{
	return (bitangents.size() > 0);
}

/* Returns wheter this vertex has indices or not */
bool Vertex::hasIndices()
{
	return (indices.size() > 0);
}

/* Returns the stride (size of the raw data per float)*/
const unsigned int Vertex::stride() {
	unsigned int stride = 0;
	if (hasVertices()) stride += 3;
	if (hasNormals()) stride += 3;
	if (hasColors()) stride += 3;
	if (hasUVs()) stride += 2;
	if (hasTangents()) stride += 3;
	return stride;
}

/* Returns the stride in vertex data*/
const unsigned int Vertex::verticeStride() {
	return 0;
}

/* Returns the first index of the first normal in the vertex data. */
const unsigned int Vertex::normalStride() {
	unsigned int stride = 3;
	if (!hasVertices()) stride -= 3;
	return stride;
}

/* Returns the first index of the first color in the vertex data. */
const unsigned int Vertex::colorStride() {
	unsigned int stride = 6;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	return stride;
}

/* Returns the first index of the first texture in the vertex data. */
const unsigned int Vertex::uvStride() {
	unsigned int stride = 9;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColors()) stride -= 3;
	return stride;
}

/* Returns the first index of the first tangent in the vertex data. */
const unsigned int Vertex::tangentStride() {
	unsigned int stride = 11;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColors()) stride -= 3;
	if (!hasUVs()) stride -= 2;
	return stride;
}

/* Returns the first index of the first bitangent in the vertex data. */
const unsigned int Vertex::bitangentStride()
{
	unsigned int stride = 14;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColors()) stride -= 3;
	if (!hasUVs()) stride -= 2;
	if (!hasTangents()) stride -= 3;
	return stride;
}

/* Prints all vertices in a human-readable format */
const void Vertex::printVertices()
{
	for (int i = 0; i < vertices.size(); i++)
		std::cout << vertices[i].x << ", " << vertices[i].y << ", " << vertices[i].z << std::endl;
}

/* Prints all normals in a human-readable format */
const void Vertex::printNormals()
{
	for (int i = 0; i < normals.size(); i++)
		std::cout << normals[i].x << ", " << normals[i].y << ", " << normals[i].z << std::endl;
}

/* Prints all colors in a human-readable format */
const void Vertex::printColors()
{
	for (int i = 0; i < colors.size(); i++)
		std::cout << colors[i].x << ", " << colors[i].y << ", " << colors[i].z << std::endl;
}

/* Prints all uvs in a human-readable format */
const void Vertex::printUVs()
{
	for (int i = 0; i < uvs.size(); i++)
		std::cout << uvs[i].x << ", " << uvs[i].y << std::endl;
}

/* Prints all tangents in a human-readable format */
const void Vertex::printTangents()
{
	for (int i = 0; i < tangents.size(); i++)
		std::cout << tangents[i].x << ", " << tangents[i].y << ", " << tangents[i].z << std::endl;
}

/* Prints all bitangents in a human-readable format */
const void Vertex::printBitangents()
{
	for (int i = 0; i < bitangents.size(); i++)
		std::cout << bitangents[i].x << ", " << bitangents[i].y << ", " << bitangents[i].z << std::endl;
}

/* Prints all indices in a human-readable format */
const void Vertex::printIndices()
{
	for (int i = 0; i < indices.size(); i += 3)
		std::cout << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
}

/* Prints vertex data in a human-readable format */
const void Vertex::printVertexData()
{
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (hasVertices())
			std::cout << "Vertices(" << vertices[i].x << ", " << vertices[i].y << ", " << vertices[i].z << "), ";
		if (hasNormals())
			std::cout << "Normals(" << normals[i].x << ", " << normals[i].y << ", " << normals[i].z << "), ";
		if (hasColors())
			std::cout << "Colors(" << colors[i].x << ", " << colors[i].y << ", " << colors[i].z << "), ";
		if (hasUVs())
			std::cout << "UVs(" << uvs[i].x << ", " << uvs[i].y << "), ";
		if (hasTangents())
			std::cout << "Tangents(" << tangents[i].x << ", " << tangents[i].y << ", " << tangents[i].z << ")";
		if (hasBitangents())
			std::cout << "Bitangents(" << bitangents[i].x << ", " << bitangents[i].y << ", " << bitangents[i].z << ")";

		std::cout << std::endl << std::endl;
	}
}

std::vector<float> Vertex::combinedVertexData()
{
	std::vector<float> raw_data;
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (hasVertices())
		{
			raw_data.push_back(vertices.at(i).x);
			raw_data.push_back(vertices.at(i).y);
			raw_data.push_back(vertices.at(i).z);
		}
		if (hasNormals())
		{
			raw_data.push_back(normals.at(i).x);
			raw_data.push_back(normals.at(i).y);
			raw_data.push_back(normals.at(i).z);
		}
		if (hasColors())
		{
			raw_data.push_back(colors.at(i).x);
			raw_data.push_back(colors.at(i).y);
			raw_data.push_back(colors.at(i).z);
		}
		if (hasUVs())
		{
			raw_data.push_back(uvs.at(i).x);
			raw_data.push_back(uvs.at(i).y);
		}
		if (hasTangents())
		{
			raw_data.push_back(tangents.at(i).x);
			raw_data.push_back(tangents.at(i).y);
			raw_data.push_back(tangents.at(i).z);
		}	
	}
	return raw_data;
}