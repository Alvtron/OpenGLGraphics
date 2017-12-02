#version 450 core

	out vec4 FragColor;

	in vec2 UV;

	uniform sampler2D scene;
	uniform sampler2D bloomBlur;
	uniform bool bloom;
	uniform float exposure;

	void main() {

		vec3 hdrColor = texture(scene, UV).rgb;
		vec3 bloomColor = texture(bloomBlur, UV).rgb;

		if (bloom) {
			// Add the original scene and the bloom scene together
			hdrColor += bloomColor;
		}

		// This function will make the result vector vary from 0 to 1 in all rgb colors, depending on the value of exposure.
		// The exposure value is controlled by the "Q" and "E" keys. By using a really high exposure value, the rgb colors will approach 1
		// (totally white color, maximum bloom). The lowest exposure value allowed is 0, which will make the rgb colors equal to 0, which is total black.
		vec3 result = vec3(1.0) - exp(-hdrColor * exposure);

		FragColor = vec4(result, 1.0);

	}