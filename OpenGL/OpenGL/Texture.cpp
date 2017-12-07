#include "Texture.h"

static int active_textures = 0;

Texture::Texture()
{
}

Texture::Texture(char const * path)
{
	glGenTextures(1, &id);

	int components;
	unsigned char *data = stbi_load(path, &width, &height, &components, 0);
	if (!data) {
		printf("Error: Texture failed to load at path: %s", path);
		stbi_image_free(data);
	}

	GLenum format;
	if (components == 1)
		format = GL_RED;
	else if (components == 3)
		format = GL_RGB;
	else if (components == 4)
		format = GL_RGBA;

	// Bind texture and generate mipmap
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Free data and unbind texture
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

}

Texture::~Texture()
{
}

void activateTexture(Texture* t)
{
	t->index = active_textures++;
}

bool createTexture1DFromPhase(Texture* t, const char* file_path)
{
	FILE* fp = fopen(file_path, "r");

	if (fp != NULL) {
		return false;
	}

	activateTexture(t);

	/* Create image */
	std::vector<uint8_t> image;
	image.reserve(1801);

	/* Read image*/
	char value[128];
	while (fgets(value, 128, fp)) {
		value[strlen(value) - 1] = '\0';
		image.push_back((uint8_t)(255 * atof(value)));
	}

	glGenTextures(1, &t->id);
	glBindTexture(GL_TEXTURE_1D, t->id);

	glTexImage1D(GL_TEXTURE_1D, 0, GL_RED, 1800, 0, GL_RED, GL_UNSIGNED_BYTE, image.data());
	glGenerateMipmap(GL_TEXTURE_1D);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	return true;
}

bool createTexture2DFromEX5(Texture* t, const char* file_path)
{
	FILE* fp = fopen(file_path, "r");

	if (fp == NULL) {
		return false;
	}

	activateTexture(t);

	/* Read header */
	fscanf(fp, "%d", &t->width);
	fscanf(fp, "%d", &t->height);

	/* Create image */
	std::vector<uint8_t> image;
	image.reserve(t->width * t->height * 4);

	/* Read image*/
	uint32_t pixel;
	while (fscanf(fp, "%d", &pixel) == 1) {
		image.push_back(pixel >> 24);
		image.push_back(pixel >> 16);
		image.push_back(pixel >> 8);
		image.push_back(pixel >> 0);
	}

	glGenTextures(1, &t->id);
	glBindTexture(GL_TEXTURE_2D, t->id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true;
}

bool createTexture3DFromEX5(Texture* t, const char* file_path)
{
	FILE* fp = fopen(file_path, "r");

	if (fp == NULL) {
		return false;
	}

	activateTexture(t);

	/* Read header */
	fscanf(fp, "%d", &t->width);
	fscanf(fp, "%d", &t->height);
	fscanf(fp, "%d", &t->depth);

	/* Create image */
	std::vector<uint8_t> image;
	image.reserve(t->width * t->height * t->depth * 4);

	/* Read image*/
	uint32_t pixel;
	while (fscanf(fp, "%d", &pixel) == 1) {
		image.push_back(pixel >> 24);
		image.push_back(pixel >> 16);
		image.push_back(pixel >> 8);
		image.push_back(pixel >> 0);
	}

	glGenTextures(1, &t->id);
	glBindTexture(GL_TEXTURE_3D, t->id);

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, t->width, t->height, t->depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
	glGenerateMipmap(GL_TEXTURE_3D);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	return true;
}