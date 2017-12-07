#version 450 core

	out vec4 FragColor;

	in vec2 UV;

	uniform sampler2D HDR_buffer;
	uniform sampler2D bloom_blur;

	uniform bool bloom;
	uniform float exposure;

	void main() {
		vec3 result = vec3(0.0f);
		vec3 hdrColor = texture(HDR_buffer, UV).rgb;
		vec3 bloomColor = texture(bloom_blur, UV).rgb;
		
		result += hdrColor;

		if (bloom) {
			// additive blending
			result += bloomColor;
		}

		// tone mapping
		vec3 mapped = vec3(1.0f) - exp(-result * exposure);

		FragColor = vec4(mapped, 1.0f);

	}