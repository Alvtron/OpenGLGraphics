#pragma once
#include "Texture.h"

class Material
{
private:
	bool diffuseBound = false, specularBound = false, normalBound = false, displacementBound = false, AOBound = false;
public:
	Texture diffuse;
	Texture specular;
	Texture normal;
	Texture displacement;
	Texture ambient_occlusion;

	Material();
	~Material();

	/* Add a diffuse texture file to this Material object. */
	void addDiffuse(const Texture &texture);
	/* Add a specular texture file to this Material object. */
	void addSpecular(const Texture &texture);
	/* Add a normal texture file to this Material object.*/
	void addNormal(const Texture &texture);
	/* Add a displacement texture file to this Material object. */
	void addDisplacement(const Texture &texture);
	/* Add a ambient oclusion texture file to this Material object. */
	void addAmbientOcclusion(const Texture &texture);

	/* Returns a bool whether this texture object has a diffuse texture file bound or not */
	const bool hasDiffuse();
	/* Returns a bool whether this texture object has a specular texture file bound or not */
	const bool hasSpecular();
	/* Returns a bool whether this texture object has a normal texture file bound or not */
	const bool hasNormal();
	/* Returns a bool whether this texture object has a displacement texture file bound or not */
	const bool hasDisplacement();
	/* Returns a bool whether this texture object has a ambient oclusion texture file bound or not */
	const bool hasAO();
	void bind();
	void unbind();
};