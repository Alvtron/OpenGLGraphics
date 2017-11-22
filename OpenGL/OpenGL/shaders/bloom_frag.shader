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
			// additive blending
			hdrColor += bloomColor;
		}

		// tone mapping
		vec3 result = vec3(1.0) - exp(-hdrColor * exposure);

		FragColor = vec4(result, 1.0);

	}