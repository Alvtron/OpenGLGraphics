#include "Mesh.h"

/* Constructor. Create a Mesh object that stores and utilizes vertex data. */
Mesh::Mesh(){}

/* Deconstructor */
Mesh::~Mesh()
{
	deAllocate();
}

/* Generate buffers and store vertex data on the GPU. Call drawObject(...) to draw it */
bool Mesh::storeOnGPU()
{
	if (vertex.hasVertices())
	{
		glGenVertexArrays(1, &VAO); // Create VAO that stores the buffer objects.
		glGenBuffers(1, &VBO); // Create VBO that stores vertex data
		glGenBuffers(1, &EBO); // Create EBO that stores indices
		glBindVertexArray(VAO); // Bind the VAO before binding and configuring buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO to the GL_ARRAY_BUFFER target
		// Copy vertex data into the VBO currently bound to the GL_ARRAY_BUFFER target
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.dataSize(), vertex.combinedVertexData().data(), GL_STATIC_DRAW);

		const unsigned int stride = vertex.stride() * sizeof(float);

		if (vertex.hasVertices()) {
			// Position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(vertex.verticeStride() * sizeof(float)));
			glEnableVertexAttribArray(0);
		}
		if (vertex.hasNormals())
		{
			// Normals coordinate attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(vertex.normalStride() * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		if (vertex.hasColors())
		{
			// Colors coordinate attribute
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(vertex.colorStride() * sizeof(float)));
			glEnableVertexAttribArray(2);
		}
		if (vertex.hasUVs())
		{
			// Texture coordinate attribute
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, (void*)(vertex.uvStride() * sizeof(float)));
			glEnableVertexAttribArray(3);
		}
		if (vertex.hasTangents())
		{
			// Tangents coordinate attribute
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (void*)(vertex.tangentStride() * sizeof(float)));
			glEnableVertexAttribArray(4);
		}
		if (vertex.hasBitangents())
		{
			// Tangents coordinate attribute
			glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, stride, (void*)(vertex.bitangentStride() * sizeof(float)));
			glEnableVertexAttribArray(5);
		}
		if (vertex.hasIndices()) {
			// Bind the EBO to the GL_ELEMENT_ARRAY_BUFFER target
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			// Copy indices data into the EBO currently bound to the GL_ELEMENT_ARRAY_BUFFER target
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vertex.indices.size(), vertex.indices.data(), GL_STATIC_DRAW);
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

/* Set draw mode. Defaults to GL_TRIANGLES */
void Mesh::setDrawMode(GLenum mode)
{
	draw_mode = mode;
}

/* Set if textures should scale with object or not. False by default*/
void Mesh::scaleTextures(const bool ENABLE)
{
	scaleTexture = ENABLE;
}

/* Draw MESH_INDICE vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, const float &rotation_degrees, const vec3 &rotation_vector, Texture &texture, const int &from_index, const int &to_index)
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
		mat4 translate = mat4::makeTranslate(position);
		mat4 rotate = mat4::makeRotate(rotation_degrees, rotation_vector);
		mat4 scale = mat4::makeScale(scale_vector);
		mat4 model = translate * rotate * scale;
		shader->setMat4("model", model);
		if (!scaleTexture)
			shader->setVec2("scale", vec2(scale_vector.x, scale_vector.y));
		else
			shader->setVec2("scale", vec2(1.0f, 1.0f));
		// Draw mesh
		if (vertex.hasIndices())
			glDrawElements(draw_mode, vertex.indices.size(), GL_UNSIGNED_INT, 0);
		else
			glDrawArrays(draw_mode, from_index, to_index);
		return true;
	}
	else
	{
		std::cout << "Mesh : drawObject() : Can't draw mesh. Mesh data is not stored on GPU. Call storeOnGPU() first!";
		return false;
	}
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, const float &rotation_degrees, const vec3 &rotation_vector, Texture &texture)
{
	return drawObject(shader, position, scale_vector, rotation_degrees, rotation_vector, texture, 0, vertex.size());
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, const vec3 &position, const float &rotation_degrees, const vec3 &rotation_vector, Texture &texture)
{
	return drawObject(shader, position, vec3(1.0f, 1.0f, 1.0f), rotation_degrees, rotation_vector, texture, 0, vertex.size());
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, const vec3 &position, const vec3 &scale_vector, Texture &texture)
{
	return drawObject(shader, position, scale_vector, 0.0f, vec3(1.0f, 1.0f, 1.0f), texture, 0, vertex.size());
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, const vec3 &position, Texture &texture)
{
	return drawObject(shader, position, vec3(1.0f, 1.0f, 1.0f), 0.0f, vec3(1.0f, 1.0f, 1.0f), texture, 0, vertex.size());
}

/* Draw vertex data from GPU */
bool Mesh::drawObject(const Shader * shader, Texture &texture)
{
	return drawObject(shader, vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), 0.0f, vec3(1.0f, 1.0f, 1.0f), texture, 0, vertex.size());
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