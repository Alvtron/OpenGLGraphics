#version 450 core

	out vec4 FragColor;

	in vec2 UV;

	uniform sampler2D image;

	// This boolean decides if we should blur horizontally or vertically
	uniform bool horizontal;
	// We assign different Gaussian weights to the horizontal or vertical samples around the current fragment.
	uniform float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

	void main() {

		// This gives us the size of a single texel
		vec2 tex_offset = 1.0 / textureSize(image, 0); 
		// Current fragment's contribution
		vec3 result = texture(image, UV).rgb * weight[0];

		if (horizontal) {

			// Blurs the image horizontally, both in positive x and negative x direction.
			for (int i = 1; i < 5; ++i) {
				result += texture(image, UV + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
				result += texture(image, UV - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
			}

		}

		else {

			// Blurs the image vertically, both in positive y and negative y direction.
			for (int i = 1; i < 5; ++i) {
				result += texture(image, UV + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
				result += texture(image, UV - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
			}

		}

		FragColor = vec4(result, 1.0);

	}