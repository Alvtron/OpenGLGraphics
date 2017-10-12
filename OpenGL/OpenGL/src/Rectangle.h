/*

Created by Thomas Angeland, student at Østfold University College, Norway.

*/

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shader.h"

class Rect
{
private:

	enum CORNERS : int
	{
		Ax = 0, Ay = 1, Az = 2, Anx = 3, Any = 4, Anz = 5, Atx = 6, Aty = 7,
		Bx = 8, By = 9, Bz = 10, Bnx = 11, Bny = 12, Bnz = 13, Btx = 14, Bty = 15,
		Cx = 16, Cy = 17, Cz = 18, Cnx = 19, Cny = 20, Cnz = 21, Ctx = 22, Cty = 23,
		Dx = 24, Dy = 25, Dz = 26, Dnx = 27, Dny = 28, Dnz = 29, Dtx = 30, Dty = 31
	};

	const float WIDTH = 1.0f, HEIGHT = 1.0f;
	const int INDICES[6] = {
		0, 1, 2, // first triangle (A,B,C)
		2, 3, 0  // second triangle (C,D,A)
	};

	float vertices[32];

	// Create VBO, VAO and EBO for GPU memory management
	unsigned int VBO, VAO, EBO;

public:

	Rect();
	Rect(float width, float height);
	Rect(float x, float y, float z);
	Rect(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float dx, float dy, float dz);
	~Rect();

	float getWidth();
	float getHeight();
	float getAreal();

	void storeOnGPU();
	void drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, unsigned int texture_diffuse, unsigned int texture_specular);
	void drawObject(Shader * shader, glm::vec3 position, glm::vec3 scale_vector, float rotation_degrees, glm::vec3 rotation_vector, unsigned int texture_diffuse, unsigned int texture_specular);
	void deAllocate();
};

