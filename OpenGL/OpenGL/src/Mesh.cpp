#include "Mesh.h"

unsigned int Mesh::num_meshes = 0;

Mesh::Mesh()
{
	glGenVertexArrays(1, &VAO); // Create VAO that stores the buffer objects.
	glGenBuffers(1, &VBO); // Create VBO that stores vertex data
	glGenBuffers(1, &EBO); // Create EBO that stores indices
	num_meshes++;
}

Mesh::~Mesh()
{
	num_meshes--;
	deAllocate();
}

void Mesh::createVertexData(const std::vector<float>& vertices, const  std::vector<float>& normals, const  std::vector<float>& colors, const  std::vector<float>& textures, const  std::vector<unsigned int>& indices)
{
	vertex_data.reserve(vertices.size() + normals.size() + colors.size() + textures.size());
	unsigned int v_index = 0, n_index = 0, c_index = 0, t_index = 0;
	while (v_index < vertices.size()) {
		vertex_data.push_back(vertices[v_index++]);
		vertex_data.push_back(vertices[v_index++]);
		vertex_data.push_back(vertices[v_index++]);
		vertex_data.push_back(normals[n_index++]);
		vertex_data.push_back(normals[n_index++]);
		vertex_data.push_back(normals[n_index++]);
		vertex_data.push_back(colors[c_index++]);
		vertex_data.push_back(colors[c_index++]);
		vertex_data.push_back(colors[c_index++]);
		vertex_data.push_back(textures[t_index++]);
		vertex_data.push_back(textures[t_index++]);
	}
	this->indices = indices;
	hasVertices = true;
	hasNormals = true;
	hasColors = true;
	hasTextures = true;
	hasIndices = true;
}

void Mesh::addVertexData(const std::vector<float> &data, VERTEX_DATA_TYPE data_type)
{
	if (data_type != MESH_INDICE)
	{
		std::vector<float> new_vertex_data;
		unsigned int index = 0, data_size = data.size(), data_index = 0, n_stride = 3, c_stride = 6, t_stride = 9;
		// Adjust strides
		if (!hasVertices) n_stride -= 3, c_stride -= 3, t_stride -= 3;
		if (!hasNormals) c_stride -= 3; t_stride -= 3;
		if (!hasColors) t_stride -= 3;
		while (data_index < data_size) {
			if (data_type == MESH_VERTICE)
			{
				new_vertex_data.insert(std::end(new_vertex_data), std::begin(data) + data_index, std::begin(data) + data_index + 3);
				data_index += 3;
			}
			else if (hasVertices)
				new_vertex_data.insert(std::end(new_vertex_data), std::begin(vertex_data) + index, std::begin(vertex_data) + index + 3);

			if (data_type == MESH_NORMAL)
			{
				new_vertex_data.insert(std::end(new_vertex_data), std::begin(data) + data_index, std::begin(data) + data_index + 3);
				data_index += 3;
			}
			else if (hasNormals)
				new_vertex_data.insert(std::end(new_vertex_data), std::begin(vertex_data) + index + n_stride, std::begin(vertex_data) + index + n_stride + 3);
			if (data_type == MESH_COLOR)
			{
				new_vertex_data.insert(std::end(new_vertex_data), std::begin(data) + data_index, std::begin(data) + data_index + 3);
				data_index += 3;
			}
			else if (hasColors)
			{
				new_vertex_data.insert(std::end(new_vertex_data), std::begin(vertex_data) + index + c_stride, std::begin(vertex_data) + index + c_stride + 3);

			}
			if (data_type == MESH_TEXTURE)
			{
				new_vertex_data.insert(std::end(new_vertex_data), std::begin(data) + data_index, std::begin(data) + data_index + 2);
				data_index += 2;
			}
			else if (hasTextures)
			{
				new_vertex_data.insert(std::end(new_vertex_data), std::begin(vertex_data) + index + t_stride, std::begin(vertex_data) + index + t_stride + 2);
			}
			index += stride();
		}
		vertex_data = new_vertex_data;
		if (data_type == MESH_VERTICE) hasVertices = true;
		if (data_type == MESH_NORMAL) hasNormals = true;
		if (data_type == MESH_COLOR) hasColors = true;
		if (data_type == MESH_TEXTURE) hasTextures = true;
	}
}

void Mesh::addIndices(const std::vector<unsigned int> &indices)
{
	this->indices = indices;
	hasIndices = true;
}

void Mesh::storeOnGPU()
{
	glBindVertexArray(VAO); // Bind the VAO before binding and configuring buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO to the GL_ARRAY_BUFFER target
	
	// Copy vertex data into the VBO currently bound to the GL_ARRAY_BUFFER target
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_data.size(), &vertex_data[0], GL_STATIC_DRAW);

	if (hasVertices) {
		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride() * sizeof(float), (void*)(VerticeStride() * sizeof(float)));
		glEnableVertexAttribArray(0);
	}
	if (hasNormals)
	{
		// Normals coordinate attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride() * sizeof(float), (void*)(normalStride() * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	if (hasColors)
	{
		// Colors coordinate attribute
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride() * sizeof(float), (void*)(colorStride() * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
	if (hasTextures)
	{
		// Texture coordinate attribute
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride() * sizeof(float), (void*)(textureStride() * sizeof(float)));
		glEnableVertexAttribArray(3);
	}	
	if (hasIndices) {
		// Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// Copy indices data into the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER target
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}
}

void Mesh::drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, unsigned int texture_diffuse, unsigned int texture_specular)
{
	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_diffuse);
	// Bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_specular);
	// Bind VAO
	glBindVertexArray(VAO);
	// Calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation_degrees), rotation_vector);
	model = glm::scale(model, scale_vector);
	shader->setMat4("model", model);
	// Draw mesh
	if (hasIndices) glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	else glDrawArrays(GL_TRIANGLES, 0, vertex_data.size() / stride());
}

void Mesh::drawObject(Shader * shader, glm::vec3 position, float rotation_degrees, glm::vec3 rotation_vector, unsigned int texture_diffuse, unsigned int texture_specular)
{
	drawObject(shader, position, glm::vec3(1.0f, 1.0f, 1.0f), rotation_degrees, rotation_vector, texture_diffuse, texture_specular);
}

void Mesh::drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, unsigned int texture_diffuse, unsigned int texture_specular)
{
	drawObject(shader, position, scale_vector, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), texture_diffuse, texture_specular);
}

void Mesh::drawObject(Shader * shader, glm::vec3 position, unsigned int texture_diffuse, unsigned int texture_specular)
{
	drawObject(shader, position, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), texture_diffuse, texture_specular);
}

void Mesh::drawObject(Shader * shader, unsigned int texture_diffuse, unsigned int texture_specular)
{
	drawObject(shader, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), texture_diffuse, texture_specular);
}

// De-allocate mesh once it has outlived it's purpose
void Mesh::deAllocate()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

unsigned int Mesh::stride() {
	unsigned int stride = 0;
	if (hasVertices) stride += 3;
	if (hasNormals) stride += 3;
	if (hasColors) stride += 3;
	if (hasTextures) stride += 2;
	return stride;
}

unsigned int Mesh::VerticeStride() {
	return 0;
}

unsigned int Mesh::normalStride() {
	unsigned int stride = 3;
	if (!hasVertices) stride -= 3;
	return stride;
}

unsigned int Mesh::colorStride() {
	unsigned int stride = 6;
	if (!hasVertices) stride -= 3;
	if (!hasNormals) stride -= 3;
	return stride;
}

unsigned int Mesh::textureStride() {
	unsigned int stride = 9;
	if (!hasVertices) stride -= 3;
	if (!hasNormals) stride -= 3;
	if (!hasColors) stride -= 3;
	return stride;
}

void Mesh::printVertices()
{
	for (int i = 0; i < vertex_data.size(); i += 11)
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i] << ", " << vertex_data[i + 1] << ", " << vertex_data[i + 2] << std::endl;
}

void Mesh::printNormals()
{
	for (int i = 0; i < vertex_data.size(); i += 11)
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 3] << ", " << vertex_data[i + 4] << ", " << vertex_data[i + 5] << std::endl;
}

void Mesh::printColors()
{
	for (int i = 0; i < vertex_data.size(); i += 11)
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 6] << ", " << vertex_data[i + 7] << ", " << vertex_data[i + 8] << std::endl;
}

void Mesh::printTextures()
{
	for (int i = 0; i < vertex_data.size(); i += 11)
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 9] << ", " << vertex_data[i + 10] << std::endl;
}

void Mesh::printIndices()
{
	for (int i = 0; i < indices.size(); i += 3)
		std::cout << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
}

void Mesh::printVertexData()
{
	unsigned int vertices_index = 0, normals_index = 0, colors_index = 0, textures_index = 0;
	for (int i = 0; i < vertex_data.size(); i += 11) {
		std::cout << "v(" << std::fixed << std::setprecision(1) << vertex_data[i] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 1] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 2] << "), n(";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 3] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 4] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 5] << "), c(";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 6] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 7] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 8] << "), t(";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 9] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 10] << ")" << std::endl;
	}
}