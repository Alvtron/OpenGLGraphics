#include "CloudTexture.h"

/* Based on the cloud processing method by Rikard Olajos,
in his master's thesis: Real-Time Rendering of Volumetric Clouds
http://lup.lub.lu.se/luur/download?func=downloadFile&recordOId=8893256&fileOId=8893258
https://github.com/rikardolajos/clouds */

GLubyte CloudTexture::structure(GLubyte pixel)
{
	return (pixel / 255.0 > 0.35) ? 1: 0;
}

int CloudTexture::process(Texture * cloud_structure, Texture cloud_texture)
{
	// Read the source texture
	std::vector<GLubyte> cloud_pixels;
	cloud_pixels.resize(cloud_texture.width * cloud_texture.height * cloud_texture.depth * 4);
	
	glBindTexture(GL_TEXTURE_3D, cloud_texture.id);
	glGetTexImage(GL_TEXTURE_3D, 0, GL_RGBA, GL_UNSIGNED_BYTE, cloud_pixels.data());

	// Set size of structure texture, Creates 4x4x4 cubes of original 128x128x128 texture
	cloud_structure->width = 32;
	cloud_structure->height = 32;
	cloud_structure->depth = 32;

	// Pick the red channel of the texture and procces it
	std::vector<GLubyte> red_channel;
	red_channel.resize(cloud_texture.width * cloud_texture.height * cloud_texture.depth);
	for (int i = 0; i < red_channel.size(); i++) {
		red_channel.at(i) = structure(cloud_pixels.at(i * 4));
	}

	std::vector<GLubyte> new_cloud_structure;
	new_cloud_structure.resize(cloud_structure->width * cloud_structure->height * cloud_structure->depth);

	// Analyze every 4x4x4 block of the cloud texture
	int inside = 0;
	for (int i = 0; i < cloud_structure->width; i++) for (int j = 0; j < cloud_structure->height; j++) for (int k = 0; k < cloud_structure->depth; k++) {

		inside = 0;

		for (int u = 0; u < 4; u++) for (int v = 0; v < 4; v++) for (int w = 0; w < 4; w++) {

			int x = i * 4 + u;
			int y = j * 4 + v;
			int z = k * 4 + w;

			inside += red_channel.at(x + y * cloud_texture.height + z * cloud_texture.height * cloud_texture.depth);
		}

		if (inside < 8)
			new_cloud_structure.at(i + j * cloud_structure->height + k * cloud_structure->height * cloud_structure->depth) = 0;
		else
			new_cloud_structure.at(i + j * cloud_structure->height + k * cloud_structure->height * cloud_structure->depth) = 255;
	}

	/* Post process -- expanding the structure to reduce artifacts */
	//GLubyte* post_pixels = (GLubyte*)calloc(cloud_structure->width * cloud_structure->height * cloud_structure->depth, sizeof(GLubyte));
	std::vector<GLubyte> post_pixels;
	post_pixels.resize(cloud_structure->width * cloud_structure->height * cloud_structure->depth);

	for (int i = 0; i < cloud_structure->width; i++) for (int j = 0; j < cloud_structure->height; j++) for (int k = 0; k < cloud_structure->depth; k++) {

		if (new_cloud_structure.at(k + j * cloud_structure->height + i * cloud_structure->height * cloud_structure->depth) == 0) {
			continue;
		}

		for (int ii = -1; ii < 2; ii++) {
			if (i + ii < 0 || i + ii >= cloud_structure->width) continue;
			for (int jj = -1; jj < 2; jj++) {
				if (j + jj < 0 || j + jj >= cloud_structure->height) continue;
				for (int kk = -1; kk < 2; kk++) {
					if (k + kk < 0 || k + kk >= cloud_structure->depth) continue;
					post_pixels.at((k + kk) + (j + jj) * cloud_structure->height + (i + ii) * cloud_structure->height * cloud_structure->depth) = 255;
				}
			}
		}
	}

	// Bind the new cloud structure texture to an unique ID
	glGenTextures(1, &cloud_structure->id);
	glBindTexture(GL_TEXTURE_3D, cloud_structure->id);

	// Assign new cloud structure texture to it's ID
	activateTexture(cloud_structure);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, cloud_structure->width, cloud_structure->height, cloud_structure->depth, 0, GL_RED, GL_UNSIGNED_BYTE, post_pixels.data());
	glGenerateMipmap(GL_TEXTURE_3D);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

	// Free memory
	cloud_pixels.clear();
	cloud_pixels.shrink_to_fit();
	red_channel.clear();
	red_channel.shrink_to_fit();
	new_cloud_structure.clear();
	new_cloud_structure.shrink_to_fit();
	post_pixels.clear();
	post_pixels.shrink_to_fit();

	return 0;
}