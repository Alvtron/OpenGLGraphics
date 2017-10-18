#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <iostream>
#include <string>

class Texture
{
private:
	static unsigned int num_textures;
	unsigned int diffuse_id, specular_id, normal_id, ao_id;
	bool diffuseBound = false, specularBound = false, normalBound = false, AOBound = false;
public:
	enum TEXTURE_TYPE : char {
		TXT_DIFFUSE = 'D',
		TXT_SPECULAR = 'S',
		TXT_NORMAL = 'N',
		TXT_AO = 'A'
	};
	Texture();
	~Texture();
	bool bindTexture(char const * path, unsigned int & id);
	bool addTexture(std::string path, TEXTURE_TYPE type);
	bool addDiffuse(std::string path);
	bool addSpecular(std::string path);
	bool addNormal(std::string path);
	bool addAO(std::string path);
	bool hasDiffuse();
	bool hasSpecular();
	bool hasNormal();
	bool hasAO();
	unsigned int diffuse();
	unsigned int specular();
	unsigned int normal();
	unsigned int ao();
};