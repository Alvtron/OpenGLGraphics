#version 450 core

out vec4 fcolor;

in vec2 UVs;

uniform sampler2D image;

// This boolean decides if we should blur horizontally or vertically
uniform bool horizontal;
// We assign different Gaussian weights to the horizontal or vertical samples around the current fragment.
uniform float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
	// This gives us the size of a single texel
	vec2 tex_offset = 1.0 / textureSize(image, 0);
	// Current fragment's contribution (we multiply the fragment with the largest weight, because it should have the
	// biggest contribution)
	vec3 result = texture(image, UVs).rgb * weight[0];

	if (horizontal) {

		// Blurs the image horizontally, both in positive x and negative x direction.
		for (int i = 1; i < 5; ++i) {
			result += texture(image, UVs + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
			result += texture(image, UVs - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
		}
	}
	else {

		// Blurs the image vertically, both in positive y and negative y direction.
		for (int i = 1; i < 5; ++i) {
			result += texture(image, UVs + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
			result += texture(image, UVs - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
		}
	}

	fcolor = vec4(result * 1, 1.0);
}