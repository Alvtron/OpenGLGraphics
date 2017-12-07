#version 450 core

out vec4 fcolor;

in vec2 UVs;

uniform sampler2D image;
uniform bool horizontal;

uniform float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {

	vec2 tex_offset = 1.0 / textureSize(image, 0);
	vec3 result = texture(image, UVs).rgb * weight[0];

	if (horizontal) {
		for (int i = 1; i < 5; ++i) {
			result += texture(image, UVs + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
			result += texture(image, UVs - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
		}
	}
	else {
		for (int i = 1; i < 5; ++i) {
			result += texture(image, UVs + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
			result += texture(image, UVs - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
		}
	}

	fcolor = vec4(result * 1, 1.0);
}