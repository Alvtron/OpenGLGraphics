#version 450 core

layout(location = 0) in vec3 vertex_position;

layout(location = 0) out vec4 fragment_color;
layout(location = 1) out vec4 bright_color;

uniform sampler3D cloud_texture;
uniform sampler3D cloud_structure;
uniform sampler2D diffuse_buffer;

uniform vec2 window_size;
uniform vec3 camera_position;
uniform vec3 sun_position;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 inv_view;
uniform mat4 inv_proj;

uniform float end = 1000.0;

float PI = 3.1415962;
float PI_r = 0.3183098;

float HG(float costheta) {
	float g = 0.4;
	return 1.25 * PI_r * (1 - pow(g, 2.0)) / pow((1 + pow(g, 2.0) - 2 * g * costheta), 1.5) + 0.5;
}

float phase(vec3 v1, vec3 v2, float t) {
	float costheta = dot(v1, v2) / length(v1) / length(v2);
	return HG(-costheta);
}

float coverage(float t) {
	return smoothstep(0.35, 0.4, t) * t;
}

float cloud_sampling_lowres(vec3 v, float delta) {
	v.y -= 80;
	vec4 texture = texture(cloud_structure, v / 500);
	return texture.r;
}

float cloud_sampling(vec3 v, float delta) {

	v.y -= 80;

	vec4 textureA = texture(cloud_texture, v / 500);

	float coverage = coverage(textureA.r);
	float bottom = smoothstep(0, 80, v.y);

	return textureA.r * coverage * bottom * delta * pow(textureA.b, 0.3) * pow(textureA.a, 0.4);
}

float cast_scatter_ray(vec3 origin, vec3 dir, float t) {
	float delta = 10.0;

	vec3 sample_point = vec3(0.0);
	float inside = 0.0;

	float phase = phase(dir, vec3(camera_position - origin), t);

	for (float t = 0.0; t < end/10; t += delta) {
		sample_point = origin + dir * t;
		inside += cloud_sampling(sample_point, delta);
	}

	float scatter = 3 * exp(-0.7 * inside) * (1.0 - exp(-0.8 * inside));

	float result = scatter * phase;
	return result;
}

// http://www.iquilezles.org/www/articles/terrainmarching/terrainmarching.htm
vec4 cast_ray(vec3 origin, vec3 dir) {
	float delta_large = 10.0;
	float delta_small = 5.0;
	float start = gl_DepthRange.near;

	vec4 result = vec4(0.0);
	vec3 cloud_bright_result = vec3(4.0, 4.0, 4.0);
	vec3 cloud_dark_result = vec3(0.416, 0.518, 0.694);
	result.rgb = cloud_dark_result;

	float length_inside = 0.0;
	bool inside = false;
	bool looking_for_new_inside = true;
	int points_inside = 0;
	vec3 sample_point = origin;

	bool first = false;
	float delta = delta_large;
	for (float t = start; t < end; t += delta) {
		sample_point = origin + dir * t;

		if (first) delta_small = 1.0;

		// Stop rays that already reached full opacity
		if (result.a == 1.0) break;

		float alpha = 0.0;
		float alpha_lowres = 0.0;
		if (!inside) {
			alpha_lowres = cloud_sampling_lowres(sample_point, delta);
			
			if (alpha_lowres > 0.001) inside = true;
			
			else looking_for_new_inside = true;
		}

		if (inside) {
			// Start of a new inside session?
			if (looking_for_new_inside) {
				// Move the starting point a large delta backwards
				t -= delta_large;
				
				if (t < gl_DepthRange.near) t = gl_DepthRange.near;

				sample_point = origin + dir * t;
				delta = delta_small;
				looking_for_new_inside = false;
				points_inside = 0;
				first = true;
			}

			// Comment this line to see cloud structure
			alpha = cloud_sampling(sample_point, delta);
			result.a += alpha;
			result.a = clamp(result.a, 0.0, 1.0);
			points_inside += 1;

			// Calculate the shadows and the scattering
			float energy = cast_scatter_ray(sample_point, normalize(sun_position - sample_point), t);
			float inside_weight = smoothstep(5, 0, points_inside);
			result.rgb += cloud_bright_result * energy * alpha;
		}

		// Check next structure block if we are still inside
		if (inside && (points_inside * delta_small) > delta_large) {
			alpha_lowres = cloud_sampling_lowres(sample_point, delta);
			if (alpha_lowres == 0.0) {
				inside = false;
				looking_for_new_inside = true;
				delta = delta_large;
			}
			points_inside = 0;
		}
	}

	return result;
}

void main() {
	// Calculate the ray.  http://antongerdelan.net/opengl/raycasting.html
	float x = 2.0 * gl_FragCoord.x / window_size.x - 1.0;
	float y = 2.0 * gl_FragCoord.y / window_size.y - 1.0;
	vec4 ray_clip = vec4(vec2(x, y), -1.0, 1.0);
	vec4 ray_view = vec4((inv_proj * ray_clip).xy, -1.0, 0.0);
	vec3 ray_world = normalize((inv_view * ray_view).xyz);

	vec4 cloud_color = cast_ray(camera_position, ray_world);

	vec4 diffuse_color = texelFetch(diffuse_buffer, ivec2(gl_FragCoord.xy), 0);

	fragment_color.a = 0.9;
	fragment_color.rgb = mix(diffuse_color.rgb, cloud_color.rgb, cloud_color.a)*0.8;

	if (dot(fragment_color.rgb, vec3(0.1126, 0.3152, 0.0722)) > 500.0) {
		bright_color = vec4(fragment_color.rgb, 1.0);
	}
}