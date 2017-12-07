#version 450 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
	vec4 result = texture(skybox, TexCoords);
	FragColor = vec4(result.x, result.y, result.z, 1.0);
}