#pragma once
#include "glm.hpp"
#include "texture.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "texture.h"
#include <vector>

/* Based on the cloud processing method by Rikard Olajos,
in his master's thesis: Real-Time Rendering of Volumetric Clouds
http://lup.lub.lu.se/luur/download?func=downloadFile&recordOId=8893256&fileOId=8893258
https://github.com/rikardolajos/clouds */

class CloudTexture {
public:
	// Return 1 if inside cloud, 0 if not.
	static GLubyte structure(GLubyte pixel);
	// Process the 3D noise texture.
	static int process(Texture* cloud_structure, Texture cloud_texture);
};