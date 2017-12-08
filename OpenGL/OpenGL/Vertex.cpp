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

Vertex::~Vertex()
{
	deAllocate();
}

void Vertex::setScale(const vec3 & scale_vector)
{
	scale = mat4::makeScale(scale_vector);
	uv_scale.x = scale_vector.x;
	uv_scale.y = scale_vector.y;
}

mat4 & Vertex::getScale()
{
	return scale;
}

vec2 & Vertex::getUVScale()
{
	return uv_scale;
}

void Vertex::setRotate(const float & rotate_degrees, const vec3 & rotate_vector)
{
	rotate = mat4::makeRotate(rotate_degrees, rotate_vector);
}

mat4 & Vertex::getRotation()
{
	return rotate;
}

void Vertex::setPosition(const vec3 & position_vector)
{
	position = mat4::makeTranslate(position_vector);
}

mat4 & Vertex::getPosition()
{
	return position;
}

const unsigned int Vertex::size()
{
	return dataSize() / stride();
}

const unsigned int Vertex::dataSize()
{
	return vertices.size() * 3 + normals.size() * 3 + colors.size() * 3 + uvs.size() * 2 + tangents.size() * 3 + bitangents.size() * 3;
}

bool Vertex::hasVertices()
{
	return (vertices.size() > 0);
}

bool Vertex::hasNormals()
{
	return (normals.size() > 0);
}

bool Vertex::hasColors()
{
	return (colors.size() > 0);
}

bool Vertex::hasUVs()
{
	return (uvs.size() > 0);
}

bool Vertex::hasTangents()
{
	return (tangents.size() > 0);
}

bool Vertex::hasBitangents()
{
	return (bitangents.size() > 0);
}

bool Vertex::hasIndices()
{
	return (indices.size() > 0);
}

const unsigned int Vertex::stride() {
	unsigned int stride = 0;
	if (hasVertices()) stride += 3;
	if (hasNormals()) stride += 3;
	if (hasColors()) stride += 3;
	if (hasUVs()) stride += 2;
	if (hasTangents()) stride += 3;
	if (hasBitangents()) stride += 3;
	return stride;
}

const unsigned int Vertex::verticeStride() {
	return 0;
}

const unsigned int Vertex::normalStride() {
	unsigned int stride = 3;
	if (!hasVertices()) stride -= 3;
	return stride;
}

const unsigned int Vertex::colorStride() {
	unsigned int stride = 6;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	return stride;
}

const unsigned int Vertex::uvStride() {
	unsigned int stride = 9;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColors()) stride -= 3;
	return stride;
}

const unsigned int Vertex::tangentStride() {
	unsigned int stride = 11;
	if (!hasVertices()) stride -= 3;
	if (!hasNormals()) stride -= 3;
	if (!hasColors()) stride -= 3;
	if (!hasUVs()) stride -= 2;
	return stride;
}

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

bool Vertex::storeOnGPU()
{
	if (hasVertices())
	{
		glGenVertexArrays(1, &VAO); // Create VAO that stores the buffer objects.
		glGenBuffers(1, &VBO); // Create VBO that stores vertex data
		glGenBuffers(1, &EBO); // Create EBO that stores indices
		glBindVertexArray(VAO); // Bind the VAO before binding and configuring buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO to the GL_ARRAY_BUFFER target								
		// Copy vertex data into the VBO currently bound to the GL_ARRAY_BUFFER target
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataSize(), data().data(), GL_STATIC_DRAW);

		const unsigned int stride = this->stride() * sizeof(float);

		if (hasVertices()) {
			// Position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(verticeStride() * sizeof(float)));
			glEnableVertexAttribArray(0);
		}
		if (hasNormals())
		{
			// Normals coordinate attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(normalStride() * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		if (hasColors())
		{
			// Colors coordinate attribute
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(colorStride() * sizeof(float)));
			glEnableVertexAttribArray(2);
		}
		if (hasUVs())
		{
			// Texture coordinate attribute
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void*)(uvStride() * sizeof(float)));
			glEnableVertexAttribArray(3);
		}
		if (hasTangents())
		{
			// Tangents coordinate attribute
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (void*)(tangentStride() * sizeof(float)));
			glEnableVertexAttribArray(4);
		}
		if (hasBitangents())
		{
			// Tangents coordinate attribute
			glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, stride, (void*)(bitangentStride() * sizeof(float)));
			glEnableVertexAttribArray(5);
		}
		if (hasIndices()) {
			// Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			// Copy indices data into the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER target
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
		}

		storedOnGPU = true;
		return true;
	}
	else
	{
		std::cout << "Mesh : storeOnGPU() : Cannot store vertex data on GPU. Vertex data is empty!";
		return false;
	}
}

void Vertex::setDrawMode(GLenum mode)
{
	draw_mode = mode;
}

void Vertex::scaleTextures(const bool ENABLE)
{
	scaleTexture = ENABLE;
}

bool Vertex::drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, const float &rotation_degrees, const vec3 &rotation_vector, Material * material)
{
	if (storedOnGPU)
	{
		// Bind textures if if it points to a texture
		if (material != nullptr) material->bind();
		// Bind VAO
		glBindVertexArray(VAO);
		// Calculate the model matrix for each object and pass it to shader before drawing
		mat4 translate = mat4::makeTranslate(position);
		mat4 rotate = mat4::makeRotate(rotation_degrees, rotation_vector);
		mat4 scale = mat4::makeScale(scale_vector);
		mat4 model = translate * this->position * rotate * this->rotate * scale * this->scale;
		shader->setMat4("model", model);
		if (!scaleTexture)
			shader->setVec2("scale", vec2(scale_vector.x * uv_scale.x, scale_vector.y * uv_scale.y));
		else
			shader->setVec2("scale", vec2(1.0f, 1.0f));
		// Draw mesh
		if (hasIndices())
			glDrawElements(draw_mode, indices.size(), GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(draw_mode, 0, size());
		// Unbind textures
		if (material != nullptr) material->unbind();
		return true;
	}
	else
	{
		std::cout << "Mesh : drawObject() : Can't draw modle. Vertex data is not stored on GPU. Call storeOnGPU() first!";
		return false;
	}
}

bool Vertex::drawObject(const Shader * shader, const vec3 & position, const float & rotation_degrees, const vec3 & rotation_vector, Material * material)
{
	return drawObject(shader, position, vec3(1.0f), rotation_degrees, rotation_vector, material);
}

bool Vertex::drawObject(const Shader * shader, const vec3 & position, const vec3 & scale_vector, Material * material)
{
	return drawObject(shader, position, scale_vector, 0.0f, vec3(1.0f), material);
}

bool Vertex::drawObject(const Shader * shader, const vec3 & position, Material * material)
{
	return drawObject(shader, position, vec3(1.0f), 0.0f, vec3(1.0f), material);
}

bool Vertex::drawObject(const Shader * shader, Material * material)
{
	return drawObject(shader, vec3(0.0f), vec3(1.0f), 0.0f, vec3(1.0f), material);
}

bool Vertex::deAllocate()
{
	if (storedOnGPU)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		return true;
	}
	else return false;
}

const void Vertex::printVertices()
{
	for (int i = 0; i < vertices.size(); i++)
		std::cout << vertices[i].x << ", " << vertices[i].y << ", " << vertices[i].z << std::endl;
}

const void Vertex::printNormals()
{
	for (int i = 0; i < normals.size(); i++)
		std::cout << normals[i].x << ", " << normals[i].y << ", " << normals[i].z << std::endl;
}

const void Vertex::printColors()
{
	for (int i = 0; i < colors.size(); i++)
		std::cout << colors[i].x << ", " << colors[i].y << ", " << colors[i].z << std::endl;
}

const void Vertex::printUVs()
{
	for (int i = 0; i < uvs.size(); i++)
		std::cout << uvs[i].x << ", " << uvs[i].y << std::endl;
}

const void Vertex::printTangents()
{
	for (int i = 0; i < tangents.size(); i++)
		std::cout << tangents[i].x << ", " << tangents[i].y << ", " << tangents[i].z << std::endl;
}

const void Vertex::printBitangents()
{
	for (int i = 0; i < bitangents.size(); i++)
		std::cout << bitangents[i].x << ", " << bitangents[i].y << ", " << bitangents[i].z << std::endl;
}

const void Vertex::printIndices()
{
	for (int i = 0; i < indices.size(); i += 3)
		std::cout << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
}

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

const void Vertex::printDataSizes()
{
	std::cout << "Vertices: " << vertices.size() << std::endl;
	std::cout << "Normals: " << normals.size() << std::endl;
	std::cout << "Color: " << colors.size() << std::endl;
	std::cout << "UVs: " << uvs.size() << std::endl;
	std::cout << "Tangents: " << tangents.size() << std::endl;
	std::cout << "Bitangents: " << bitangents.size() << std::endl;
	std::cout << "Indices: " << indices.size() << std::endl;
}

std::vector<float> Vertex::data()
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
		if (hasBitangents())
		{
			raw_data.push_back(bitangents.at(i).x);
			raw_data.push_back(bitangents.at(i).y);
			raw_data.push_back(bitangents.at(i).z);
		}
	}
	return raw_data;
}

void Vertex::createNormals() {
	normals.clear();

	if (hasIndices())
	{
		for (unsigned int i = 0; i < indices.size(); i += 3) {
			vec3 p1 = vertices.at(indices.at(i + 0));
			vec3 p2 = vertices.at(indices.at(i + 1));
			vec3 p3 = vertices.at(indices.at(i + 2));

			vec3 U = vec3(p2 - p1);
			vec3 V = vec3(p3 - p1);

			vec3 normal = vec3::cross(U, V);

			normals.insert(normals.end(), 3, normal);
		}
	}
	else {
		for (unsigned int i = 0; i < size(); i += 3) {
			vec3 p1 = vertices.at(i + 0);
			vec3 p2 = vertices.at(i + 1);
			vec3 p3 = vertices.at(i + 2);

			vec3 U = vec3(p2 - p1);
			vec3 V = vec3(p3 - p1);

			vec3 normal = vec3::cross(U, V);

			normals.insert(normals.end(), 3, normal);
		}
	}
}

void Vertex::setColor(const vec3 &color) {
	colors = std::vector<vec3>(size(), color);
}

void Vertex::calculateTangents() {

	// Remove any previous tangents and bitangents
	tangents.clear();
	bitangents.clear();

	if (hasIndices())
	{
		for (unsigned int i = 0; i < indices.size(); i += 3) {
			// Shortcuts for vertices
			vec3 p1 = vertices.at(indices.at(i + 0));
			vec3 p2 = vertices.at(indices.at(i + 1));
			vec3 p3 = vertices.at(indices.at(i + 2));

			// Shortcuts for UVs
			vec2 uv1 = uvs.at(indices.at(i + 0));
			vec2 uv2 = uvs.at(indices.at(i + 1));
			vec2 uv3 = uvs.at(indices.at(i + 2));

			// Edges of the triangle : postion delta
			vec3 deltaPos1 = p2 - p1;
			vec3 deltaPos2 = p3 - p1;

			// UV delta
			vec2 deltaUV1 = uv2 - uv1;
			vec2 deltaUV2 = uv3 - uv1;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
			vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

			// Set the same tangent for all three vertices of the triangle.
			// They will be merged later, in vboindexer.cpp
			tangents.push_back(tangent);
			tangents.push_back(tangent);
			tangents.push_back(tangent);

			// Same thing for binormals
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
		}
	}
	else {
		for (unsigned int i = 0; i < size(); i += 3) {
			// Shortcuts for vertices
			vec3 p1 = vertices.at(i + 0);
			vec3 p2 = vertices.at(i + 1);
			vec3 p3 = vertices.at(i + 2);

			// Shortcuts for UVs
			vec2 uv1 = uvs.at(i + 0);
			vec2 uv2 = uvs.at(i + 1);
			vec2 uv3 = uvs.at(i + 2);

			// Edges of the triangle : postion delta
			vec3 deltaPos1 = p2 - p1;
			vec3 deltaPos2 = p3 - p1;

			// UV delta
			vec2 deltaUV1 = uv2 - uv1;
			vec2 deltaUV2 = uv3 - uv1;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
			vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

			// Set the same tangent for all three vertices of the triangle.
			// They will be merged later, in vboindexer.cpp
			tangents.push_back(tangent);
			tangents.push_back(tangent);
			tangents.push_back(tangent);

			// Same thing for binormals
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
			bitangents.push_back(bitangent);
		}
	}
}

std::vector<vec3> Vertex::unwrap(const std::vector<vec3> & vertex_data) {
	std::vector<vec3> unwrapped_data;
	unwrapped_data.reserve(indices.size());
	for (unsigned int indice : indices) {
		unwrapped_data.push_back(vertex_data.at(indice));
	}
	return unwrapped_data;
}

std::vector<vec2> Vertex::unwrap(const std::vector<vec2> & vertex_data) {
	std::vector<vec2> unwrapped_data;
	unwrapped_data.reserve(indices.size());
	for (unsigned int indice : indices) {
		unwrapped_data.push_back(vertex_data.at(indice));
	}
	return unwrapped_data;
}

void Vertex::subdivide(const unsigned int & divitions)
{
	if (hasIndices())
	{
		if (hasVertices()) vertices = unwrap(vertices);
		if (hasNormals()) normals = unwrap(normals);
		if (hasColors()) colors = unwrap(colors);
		if (hasUVs()) uvs = unwrap(uvs);
		if (hasTangents()) tangents = unwrap(tangents);
		if (hasBitangents()) bitangents = unwrap(bitangents);
		indices.clear();
	}	

	unsigned int times = (divitions < 7) ? divitions : 6;

	for (int d = 0; d < times; d++)
	{
		if (hasVertices()) vertices = subdivide(vertices);
		if (hasNormals()) normals = subdivide(normals);
		if (hasColors()) colors = subdivide(colors);
		if (hasUVs()) uvs = subdivide(uvs);
		if (hasTangents()) tangents = subdivide(tangents);
		if (hasBitangents()) bitangents = subdivide(bitangents);
	}
}

std::vector<vec3> Vertex::subdivide(const std::vector<vec3>& vertex_data)
{
	std::vector<vec3> subdivided;
	for (unsigned int index = 0; index < vertex_data.size(); index += 3)
	{
		// Vertices

		vec3 v1 = vertex_data.at(index + 0);
		vec3 v2 = vertex_data.at(index + 1);
		vec3 v3 = vertex_data.at(index + 2);

		vec3 va = vec3::midpoint(v1, v2);
		vec3 vb = vec3::midpoint(v2, v3);
		vec3 vc = vec3::midpoint(v1, v3);

		subdivided.push_back(v1);
		subdivided.push_back(va);
		subdivided.push_back(vc);

		subdivided.push_back(va);
		subdivided.push_back(vb);
		subdivided.push_back(vc);

		subdivided.push_back(va);
		subdivided.push_back(v2);
		subdivided.push_back(vb);

		subdivided.push_back(vc);
		subdivided.push_back(vb);
		subdivided.push_back(v3);
	}
	return subdivided;
}

std::vector<vec2> Vertex::subdivide(const std::vector<vec2>& vertex_data)
{
	std::vector<vec2> subdivided;
	for (unsigned int index = 0; index < vertex_data.size(); index += 3)
	{
		// Vertices

		vec2 v1 = vertex_data.at(index + 0);
		vec2 v2 = vertex_data.at(index + 1);
		vec2 v3 = vertex_data.at(index + 2);

		vec2 va = vec2::midpoint(v1, v2);
		vec2 vb = vec2::midpoint(v2, v3);
		vec2 vc = vec2::midpoint(v1, v3);

		subdivided.push_back(v1);
		subdivided.push_back(va);
		subdivided.push_back(vc);

		subdivided.push_back(va);
		subdivided.push_back(vb);
		subdivided.push_back(vc);

		subdivided.push_back(va);
		subdivided.push_back(v2);
		subdivided.push_back(vb);

		subdivided.push_back(vc);
		subdivided.push_back(vb);
		subdivided.push_back(v3);
	}
	return subdivided;
}