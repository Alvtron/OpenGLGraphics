/*

Created by Thomas Angeland, student at Østfold University College, Norway.

Refferences:

#1	Lectures, resources and examples by Lars Vidar Magnusson. Sourced 27.09.2017 from http://it.hiof.no/~larsvmag/itf21215_17/index.html.
Following his lectures and examples.

#2	LearnOpenGL articles by Joey de Vries. Sourced 27.09.2017 from https://learnopengl.com/.
My camera class is heavily based on Joey de Vries' camera class:
https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h (sourced 27.09.2017).
The shader class is created by Joey de Vries':
https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h (sourced 27.09.2017).
Joey de Vries code-examples on LearnOpenGL.com is licensed under
Creative Commons CC BY-NC 4.0 (https://creativecommons.org/licenses/by-nc/4.0/legalcode)

#3	"Rooms and Mazes: A Procedural Dungeon Generator" by Bob Nystrom (21.12.2014).
Sourced 27.09.2017 from http://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/.
My dungeon generator is written entirely by me, but based on Nystrom's guide.

#4	Hundreds of Stack Overflow articles. Thank God that webpage exists.

*/

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shader.h"

class Cube
{
private:
	
	const int INDICES[36] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		8, 9, 10,
		10, 11, 8,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	float vertices[192] = {
		// Positions			// Normals				// Texture coords
		// Front
		-0.5f, -0.5f, -0.5f,	+0.0f, +0.0f, -1.0f,	0.0f, 0.0f,
		+0.5f, -0.5f, -0.5f,	+0.0f, +0.0f, -1.0f,	1.0f, 0.0f,
		+0.5f, +0.5f, -0.5f,	+0.0f, +0.0f, -1.0f,	1.0f, 1.0f,
		-0.5f, +0.5f, -0.5f,	+0.0f, +0.0f, -1.0f,	0.0f, 1.0f,
		// Back
		-0.5f, -0.5f, +0.5f,	+0.0f, +0.0f, +1.0f,	0.0f, 0.0f,
		+0.5f, -0.5f, +0.5f,	+0.0f, +0.0f, +1.0f,	1.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,	+0.0f, +0.0f, +1.0f,	1.0f, 1.0f,
		-0.5f, +0.5f, +0.5f,	+0.0f, +0.0f, +1.0f,	0.0f, 1.0f,
		// Left
		-0.5f, -0.5f, +0.5f,	-1.0f, +0.0f, +0.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f, +0.0f, +0.0f,	1.0f, 0.0f,
		-0.5f, +0.5f, -0.5f,	-1.0f, +0.0f, +0.0f,	1.0f, 1.0f,
		-0.5f, +0.5f, +0.5f,	-1.0f, +0.0f, +0.0f,	0.0f, 1.0f,
		// Right
		+0.5f, -0.5f, -0.5f,	+1.0f, +0.0f, +0.0f,	0.0f, 0.0f,
		+0.5f, -0.5f, +0.5f,	+1.0f, +0.0f, +0.0f,	1.0f, 0.0f,
		+0.5f, +0.5f, +0.5f,	+1.0f, +0.0f, +0.0f,	1.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,	+1.0f, +0.0f, +0.0f,	0.0f, 1.0f,
		// Bottom
		-0.5f, -0.5f, -0.5f,	+0.0f, -1.0f, +0.0f,	0.0f, 1.0f,
		+0.5f, -0.5f, -0.5f,	+0.0f, -1.0f, +0.0f,	1.0f, 1.0f,
		+0.5f, -0.5f, +0.5f,	+0.0f, -1.0f, +0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, +0.5f,	+0.0f, -1.0f, +0.0f,	0.0f, 0.0f,
		// Top
		-0.5f, +0.5f, -0.5f,	+0.0f, +1.0f, +0.0f,	0.0f, 1.0f,
		+0.5f, +0.5f, -0.5f,	+0.0f, +1.0f, +0.0f,	1.0f, 1.0f,
		+0.5f, +0.5f, +0.5f,	+0.0f, +1.0f, +0.0f,	1.0f, 0.0f,
		-0.5f, +0.5f, +0.5f,	+0.0f, +1.0f, +0.0f,	0.0f, 0.0f,
	};

	// Create VBO, VAO and EBO for GPU memory management
	unsigned int VBO, VAO, EBO;
public:
	Cube();
	~Cube();
	float getWidth();
	float getHeight();
	float getVolume();
	void storeOnGPU();
	void drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, unsigned int texture_diffuse, unsigned int texture_specular);
	void drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, unsigned int texture_diffuse, unsigned int texture_specular);
	void deAllocate();
};

