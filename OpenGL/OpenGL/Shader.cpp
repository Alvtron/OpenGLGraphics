#include "Shader.h"

char* Shader::readFile(const char* file_path)
{
	char* file_contents;
	long input_file_size;

	FILE* input_file = fopen(file_path, "rb");
	if (input_file == NULL) {
		printf("Error: Unable to open file: %s\n", file_path);
		return NULL;
	}
	fseek(input_file, 0, SEEK_END);
	input_file_size = ftell(input_file);
	rewind(input_file);
	file_contents = (char*)malloc((input_file_size + 1) * (sizeof(char)));
	fread(file_contents, sizeof(char), input_file_size, input_file);
	fclose(input_file);
	file_contents[input_file_size] = 0;

	return file_contents;
}

int Shader::init(const char* vertex_shader_path, const char* fragment_shader_path)
{
	int success;
	char infoLog[512];
	char* vertex_source = readFile(vertex_shader_path);
	char* fragment_source = readFile(fragment_shader_path);

	if (vertex_source == NULL) {
		printf("Error: Vertex Shader is empty\n", vertex_shader_path);
		return -1;
	}

	if (fragment_source == NULL) {
		printf("Error: Fragment Shader is empty\n", vertex_shader_path);
		return -1;
	}

	strcpy(vertex_path, vertex_shader_path);
	strcpy(fragment_path, fragment_shader_path);

	// Compile the vertex shader
	printf("Compiling: %s\n", vertex_shader_path);
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_source, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "Error: Vertex compilation failed!\n" << infoLog << std::endl;
	};
	// Compile the fragment shader
	printf("Compiling: %s\n", vertex_shader_path);
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_source, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "Error: Fragment compilation failed!\n" << infoLog << std::endl;
	};
	// Link vertex shader and fragment shader
	printf("Linking: %s and %s\n", vertex_shader_path, fragment_shader_path);
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error: Shader linking failed!\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	return 0;
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const char* name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::setBool(std::string name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const char* name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setInt(std::string name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const char* name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setFloat(std::string name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const char* name, const vec2 & value) const
{
	float temp[] = { value.x, value.y };
	glUniform2fv(glGetUniformLocation(ID, name), 1, temp);
}

void Shader::setVec2(std::string name, const vec2 & value) const
{
	float temp[] = { value.x, value.y };
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}


void Shader::setVec2(const char* name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name), x, y);
}

void Shader::setVec3(const char* name, const vec3 & value) const
{
	float temp[] = { value.x, value.y, value.z };
	glUniform3fv(glGetUniformLocation(ID, name), 1, temp);
}

void Shader::setVec3(std::string name, const vec3 & value) const
{
	float temp[] = { value.x, value.y, value.z };
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}

void Shader::setVec3(const char* name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name), x, y, z);
}

void Shader::setVec4(const char* name, const vec4 & value) const
{
	float temp[] = { value.x, value.y, value.z, value.w };
	glUniform4fv(glGetUniformLocation(ID, name), 1, temp);
}

void Shader::setVec4(std::string name, const vec4 & value) const
{
	float temp[] = { value.x, value.y, value.z, value.w };
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, temp);
}


void Shader::setVec4(const char* name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
}

void Shader::setMat2(const char* name, const mat2 & mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, mat.matrix);
}

void Shader::setMat2(std::string name, const mat2 & mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.matrix);
}

void Shader::setMat3(const char* name, const mat3 & mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, mat.matrix);
}

void Shader::setMat3(std::string name, const mat3 & mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.matrix);
}

void Shader::setMat4(const char* name, const mat4 & mat) const
{
	glUseProgram(ID);
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, mat.matrix);
}

void Shader::setMat4(std::string name, const mat4 & mat) const
{
	glUseProgram(ID);
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat.matrix);
}

void Shader::setTexture1D(Texture t, const char* name)
{
	glUseProgram(ID);
	GLint uni = glGetUniformLocation(ID, name);
	glUniform1i(uni, t.index);
	glActiveTexture(GL_TEXTURE0 + t.index);
	glBindTexture(GL_TEXTURE_1D, t.id);
}

void Shader::setTexture2D(Texture t, const char* name)
{
	glUseProgram(ID);
	GLint uni = glGetUniformLocation(ID, name);
	glUniform1i(uni, t.index);
	glActiveTexture(GL_TEXTURE0 + t.index);
	glBindTexture(GL_TEXTURE_2D, t.id);
}

void Shader::setTexture3D(Texture t, const char* name)
{
	glUseProgram(ID);
	GLint uni = glGetUniformLocation(ID, name);
	glUniform1i(uni, t.index);
	glActiveTexture(GL_TEXTURE0 + t.index);
	glBindTexture(GL_TEXTURE_3D, t.id);
}