#include "Mesh.h"

unsigned int Mesh::num_meshes = 0;

Mesh::Mesh()
{
	num_meshes++;
}

Mesh::~Mesh()
{
	num_meshes--;
	deAllocate(); // De-allocate mesh once it has outlived it's purpose
}

void Mesh::storeOnGPU()
{
	// Combine vectors into one vector
	std::vector<float> vertex_data;
	vertex_data.resize(vertices.size() + normals.size() + colors.size() + textures.size());
	unsigned int i = 0, v_index = 0, n_index = 0, c_index = 0, t_index = 0;
	while(v_index < vertices.size()) {
		vertex_data[i++] = vertices[v_index++];
		vertex_data[i++] = vertices[v_index++];
		vertex_data[i++] = vertices[v_index++];
		vertex_data[i++] = normals[n_index++];
		vertex_data[i++] = normals[n_index++];
		vertex_data[i++] = normals[n_index++];
		vertex_data[i++] = colors[c_index++];
		vertex_data[i++] = colors[c_index++];
		vertex_data[i++] = colors[c_index++];
		vertex_data[i++] = textures[t_index++];
		vertex_data[i++] = textures[t_index++];
	}

	glGenVertexArrays(1, &VAO); // Create VAO that stores the buffer objects.
	glGenBuffers(1, &VBO); // Create VBO that stores vertex data
	glGenBuffers(1, &EBO); // Create EBO that stores indices

	glBindVertexArray(VAO); // Bind the VAO before binding and configuring buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO to the GL_ARRAY_BUFFER target
	
	// Copy vertex data into the VBO currently bound to the GL_ARRAY_BUFFER target
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_data.size(), &vertex_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target
	// Copy indices data into the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER target
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normals coordinate attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Colors coordinate attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// Texture coordinate attribute
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);
}

void Mesh::drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, unsigned int texture_diffuse, unsigned int texture_specular)
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
	model = glm::scale(model, scale_vector);

	shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
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

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::deAllocate()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::printVertices()
{
	unsigned int vertices_index = 0, normals_index = 0, colors_index = 0, textures_index = 0;
	while (vertices_index < vertices.size()) { 
		std::cout << "v(" << std::fixed << std::setprecision(1) << vertices[vertices_index++] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertices[vertices_index++] << ", ";
		std::cout << std::fixed << std::setprecision(1) << vertices[vertices_index++] << "), n(";
		std::cout << std::fixed << std::setprecision(1) << normals[normals_index++] << ", ";
		std::cout << std::fixed << std::setprecision(1) << normals[normals_index++] << ", ";
		std::cout << std::fixed << std::setprecision(1) << normals[normals_index++] << "), c(";
		std::cout << std::fixed << std::setprecision(1) << colors[colors_index++] << ", ";
		std::cout << std::fixed << std::setprecision(1) << colors[colors_index++] << ", ";
		std::cout << std::fixed << std::setprecision(1) << colors[colors_index++] << "), t(";
		std::cout << std::fixed << std::setprecision(1) << textures[textures_index++] << ", ";
		std::cout << std::fixed << std::setprecision(1) << textures[textures_index++] << ")" << std::endl;
	}
}
