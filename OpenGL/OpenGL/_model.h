#ifndef MODEL_H
#define MODEL_H

#include "GL/glew.h"
#include "_shader.h"
#include "glm.hpp"

typedef struct _Model _Model;
struct Model {
	_Shader shader;
	GLuint vertex_array_object;
	int triangles;
	
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

int model_load_obj(_Model* m, const char* file_path);
void model_render(_Model m);
glm::mat4 model_model_matrix(_Model m);

#endif