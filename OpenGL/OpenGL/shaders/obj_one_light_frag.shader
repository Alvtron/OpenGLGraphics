#version 450 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	sampler2D displacement;
	sampler2D AO;
	float shininess;
};

struct Light {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Point;
in vec3 Normal;
in vec3 Color;
in vec2 UV;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	// properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - Point);
	vec3 result = vec3(0.0f);

	vec3 lightDir = normalize(light.position - Point);
	// diffuse shading
	float diff = max(dot(norm, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	// attenuation
	float distance = length(light.position - Point);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	result = (ambient + diffuse + specular);
	
	// check whether result is higher than some threshold, if so, output as bloom threshold color
	float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
	if (brightness > 1.0)
		BrightColor = vec4(result, 1.0);
	else
		BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
	FragColor = vec4(result, 1.0);
}