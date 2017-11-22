#version 450 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
	vec4 result = texture(skybox, TexCoords);
	FragColor = vec4(result.x * 0.3, result.y * 0.3, result.z * 0.3, 1.0);
}