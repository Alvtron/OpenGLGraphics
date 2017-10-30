#include "Mesh.h"

unsigned int Mesh::num_meshes = 0;

/* Create a Mesh object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
Mesh::Mesh()
{
	num_meshes++;
}

/* Create a Mesh object that stores vertex data: vertices, normals, colors, textures and indices. Call createVertexData(...) to change vertex data. */
bool Mesh::createVertexData(const std::vector<glm::vec3>& vertices, const  std::vector<glm::vec3>& normals, const  std::vector<glm::vec3>& colors, const  std::vector<glm::vec2>& textures, const  std::vector<unsigned int>& indices)
{
	if (indices.size() < 1) {
		std::cout << "Mesh : createVertexData() : Cannot create vertex data. ";
		if (indices.size() < 1)
		{
			std::cout << "Indices vector is empty! " << std::endl;
			return false;
		}
	}
	else
	{
		createVertexData(vertices, normals, colors, textures);
		this->indices = indices;
		hasIndices = true;
		return true;
	}
}

bool Mesh::createVertexData(const std::vector<glm::vec3>& vertices, const  std::vector<glm::vec3>& normals, const  std::vector<glm::vec3>& colors, const  std::vector<glm::vec2>& textures)
{
	if (vertices.size() < 1 || normals.size() < 1 || colors.size() < 1 || textures.size() < 1) {
		std::cout << "Mesh : createVertexData() : Cannot create vertex data. ";
		if (vertices.size() < 1)
		{
			std::cout << "Vertices vector is empty! " << std::endl;
			return false;
		}
		if (normals.size() < 1)
		{
			std::cout << "Normals vector is empty! " << std::endl;
			return false;
		}
		if (colors.size() < 1)
		{
			std::cout << "Colors vector is empty! " << std::endl;
			return false;
		}
		if (textures.size() < 1)
		{
			std::cout << "Textures vector is empty! " << std::endl;
			return false;
		}
	}
	else {
		vertex_data.reserve(vertices.size() * 3 + normals.size() * 3 + colors.size() * 3 + textures.size() * 2);
		unsigned int v_index = 0, n_index = 0, c_index = 0, t_index = 0;
		while (v_index < vertices.size()) {
			vertex_data.push_back(vertices.at(v_index).x);
			vertex_data.push_back(vertices.at(v_index).y);
			vertex_data.push_back(vertices.at(v_index++).z);
			vertex_data.push_back(normals.at(n_index).x);
			vertex_data.push_back(normals.at(n_index).y);
			vertex_data.push_back(normals.at(n_index++).z);
			vertex_data.push_back(colors.at(c_index).x);
			vertex_data.push_back(colors.at(c_index).y);
			vertex_data.push_back(colors.at(c_index++).z);
			vertex_data.push_back(textures.at(t_index).x);
			vertex_data.push_back(textures.at(t_index++).y);
		}
		hasVertices = true;
		hasNormals = true;
		hasColors = true;
		hasTextures = true;
		return true;
	}
}

/* Deconstructor */
Mesh::~Mesh()
{
	num_meshes--;
	deAllocate();
}

/* Change or add vertex data. Specify vertex datatype, VERTEX_DATA_TYPE{MESH_VERTICE, MESH_NORMAL, MESH_COLOR, MESH_TEXTURE or MESH_INDICE}. If data already exists, it will just overwrite it. */
bool Mesh::addVertexData(const std::vector<glm::vec3> &data, VERTEX_DATA_TYPE data_type)
{
	if (data_type != MESH_INDICE)
	{
		if (data.size() > 0)
		{

			unsigned int vertex_stride = stride();
			unsigned int stride;
			if (data_type == MESH_VERTICE) stride = verticeStride();
			else if (data_type == MESH_NORMAL) stride = normalStride();
			else if (data_type == MESH_COLOR) stride = colorStride();
			else if (data_type == MESH_TEXTURE) stride = textureStride();

			// Vertices
			if ((data_type == MESH_VERTICE && hasVertices) || (data_type == MESH_NORMAL && hasNormals) || (data_type == MESH_COLOR && hasColors) || (data_type == MESH_TEXTURE && hasTextures))
			{
				for (int i = 0; i < data.size(); i++)
				{
					vertex_data.at(vertex_stride * i + stride + 0) = data[i].x;
					vertex_data.at(vertex_stride * i + stride + 1) = data[i].y;
					if (data_type != MESH_TEXTURE) vertex_data.at(vertex_stride * i + stride + 2) = data[i].z;
				}
			}
			else
			{
				if (data_type != MESH_TEXTURE)
					vertex_data.reserve(vertex_data.size() + data.size() * 3);
				else
					vertex_data.reserve(vertex_data.size() + data.size() * 2);
				if (vertex_data.empty())
				{
					for (int i = 0; i < data.size(); i++)
					{
						vertex_data.push_back(data[i].x);
						vertex_data.push_back(data[i].y);
						if (data_type != MESH_TEXTURE) vertex_data.push_back(data[i].z);
					}
				}
				else
				{
					for (int i = 0; i < data.size(); i++)
					{
						vertex_data.insert(std::begin(vertex_data) + vertex_stride * i + stride + 0, data[i].x);
						vertex_data.insert(std::begin(vertex_data) + vertex_stride * i + stride + 1, data[i].y);
						if (data_type != MESH_TEXTURE) vertex_data.insert(std::begin(vertex_data) + vertex_stride * i + stride + 2, data[i].z);
					}
				}
				if (data_type == MESH_VERTICE) hasVertices = true;
				else if (data_type == MESH_NORMAL) hasNormals = true;
				else if (data_type == MESH_COLOR) hasColors = true;
				else if (data_type == MESH_TEXTURE) hasTextures = true;
			}
			return true;
		}
		
		else
		{
			std::cout << "Mesh : addVertexData() : Cannot add vertex data. Data is empty!";
			return false;
		}
	}
	else
	{
		std::cout << "Mesh : addVertexData() : Cannot add vertex data. Data is of type indice. Use function Mesh::addIndices()";
		return false;
	}
}

/* Add/replace indices */
bool Mesh::addIndices(const std::vector<unsigned int> &indices)
{
	if (indices.size() > 0)
	{
		this->indices = indices;
		hasIndices = true;
		return true;
	}
	else
	{
		std::cout << "Mesh : addIndices() : Cannot add indices. Data is empty!";
		return false;
	}
}

/* Generate buffers and store vertex data on the GPU. Call drawObject(...) to draw it */
bool Mesh::storeOnGPU()
{
	if (vertex_data.size() > 0)
	{
		if (hasVertices)
		{
			glGenVertexArrays(1, &VAO); // Create VAO that stores the buffer objects.
			glGenBuffers(1, &VBO); // Create VBO that stores vertex data
			glGenBuffers(1, &EBO); // Create EBO that stores indices

			glBindVertexArray(VAO); // Bind the VAO before binding and configuring buffers
			glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO to the GL_ARRAY_BUFFER target
			// Copy vertex data into the VBO currently bound to the GL_ARRAY_BUFFER target
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_data.size(), &vertex_data[0], GL_STATIC_DRAW);

			if (hasVertices) {
				// Position attribute
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride() * sizeof(float), (void*)(verticeStride() * sizeof(float)));
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
			storedOnGPU = true;
			return true;
		}
		else
		{
			std::cout << "Mesh : storeOnGPU() : Cannot store vertex data on GPU. Has no vertices!";
			return false;
		}
	}
	else
	{
		std::cout << "Mesh : storeOnGPU() : Cannot store vertex data on GPU. Vertex data is empty!";
		return false;
	}
}

bool Mesh::setDrawMode(GLenum mode)
{
	if (mode == MESH_VERTICE || mode == MESH_NORMAL || mode == MESH_COLOR || mode == MESH_TEXTURE)
	{
		draw_mode = mode;
		return true;
	}
	else
	{
		std::cout << "Mesh : setDrawMode() : Draw mode " << mode << " is not valid";
		return false;
	}
}
/* Draw MESH_INDICE vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, Texture texture, int from_index, int to_index)
{
	if (storedOnGPU)
	{
		// Bind diffuse map
		if (texture.hasDiffuse())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.getDiffuse());
		}
		// Bind specular map
		if (texture.hasSpecular())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture.getSpecular());
		}
		// Bind normal map
		if (texture.hasNormal())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture.getNormal());
		}
		// Bind displacement map
		if (texture.hasDisplacement())
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, texture.getDisplacement());
		}
		// Bind ambient oclusion map
		if (texture.hasAO())
		{
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, texture.getAO());
		}
		// Bind VAO
		glBindVertexArray(VAO);
		// Calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model;
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotation_degrees), rotation_vector);
		model = glm::scale(model, scale_vector);
		shader->setMat4("model", model);
		// Draw mesh
		if (hasIndices) glDrawElements(draw_mode, indices.size(), GL_UNSIGNED_INT, 0);
		else glDrawArrays(draw_mode, from_index, to_index);
		return true;
	}
	else
	{
		std::cout << "Mesh : drawObject() : Can't draw mesh. Mesh data is not stored on GPU. Call storeOnGPU() first!";
		return false;
	}
}

bool Mesh::drawObject(const Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, const Texture texture)
{
	return drawObject(shader, position, scale_vector, rotation_degrees, rotation_vector, texture, 0, vertex_data.size() / stride());
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, glm::vec3 position, float rotation_degrees, glm::vec3 rotation_vector, const Texture texture)
{
	return drawObject(shader, position, glm::vec3(1.0f, 1.0f, 1.0f), rotation_degrees, rotation_vector, texture, 0, vertex_data.size() / stride());
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, glm::vec3 position, glm::vec3 scale_vector, const Texture texture)
{
	return drawObject(shader, position, scale_vector, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), texture, 0, vertex_data.size() / stride());
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, glm::vec3 position, const Texture texture)
{
	return drawObject(shader, position, glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), texture, 0, vertex_data.size() / stride());
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, const Texture texture)
{
	return drawObject(shader, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), texture, 0, vertex_data.size() / stride());
}

/* De-allocate vertex data once it has outlived it's purpose */
bool Mesh::deAllocate()
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

/* Returns the stride in vertex data*/
unsigned int Mesh::stride() {
	unsigned int stride = 0;
	if (hasVertices) stride += 3;
	if (hasNormals) stride += 3;
	if (hasColors) stride += 3;
	if (hasTextures) stride += 2;
	return stride;
}

/* Returns the stride in vertex data*/
unsigned int Mesh::verticeStride() {
	return 0;
}

/* Returns the first index of the first normal in the vertex data. */
unsigned int Mesh::normalStride() {
	unsigned int stride = 3;
	if (!hasVertices) stride -= 3;
	return stride;
}

/* Returns the first index of the first color in the vertex data. */
unsigned int Mesh::colorStride() {
	unsigned int stride = 6;
	if (!hasVertices) stride -= 3;
	if (!hasNormals) stride -= 3;
	return stride;
}

/* Returns the first index of the first texture in the vertex data. */
unsigned int Mesh::textureStride() {
	unsigned int stride = 9;
	if (!hasVertices) stride -= 3;
	if (!hasNormals) stride -= 3;
	if (!hasColors) stride -= 3;
	return stride;
}

/* Prints all vertices in a human-readable format */
void Mesh::printVertices()
{
	for (int i = 0; i < vertex_data.size(); i += 11)
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i] << ", " << vertex_data[i + 1] << ", " << vertex_data[i + 2] << std::endl;
}

/* Prints all normals in a human-readable format */
void Mesh::printNormals()
{
	for (int i = 0; i < vertex_data.size(); i += 11)
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 3] << ", " << vertex_data[i + 4] << ", " << vertex_data[i + 5] << std::endl;
}

/* Prints all colors in a human-readable format */
void Mesh::printColors()
{
	for (int i = 0; i < vertex_data.size(); i += 11)
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 6] << ", " << vertex_data[i + 7] << ", " << vertex_data[i + 8] << std::endl;
}

/* Prints all textures in a human-readable format */
void Mesh::printTextures()
{
	for (int i = 0; i < vertex_data.size(); i += 11)
		std::cout << std::fixed << std::setprecision(1) << vertex_data[i + 9] << ", " << vertex_data[i + 10] << std::endl;
}

/* Prints all indices in a human-readable format */
void Mesh::printIndices()
{
	for (int i = 0; i < indices.size(); i += 3)
		std::cout << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
}

/* Prints vertex data in a human-readable format */
void Mesh::printVertexData()
{
	if (hasVertices && hasNormals && hasColors && hasTextures) {
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
}