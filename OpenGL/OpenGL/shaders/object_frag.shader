#version 450 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	sampler2D displacement;
	sampler2D AO;
	float shininess;
}; 

struct DirectionLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define MAX_LIGHTS 20
#define MAX_DIRECTIONAL_LIGHTS 20
#define MAX_POINT_LIGHTS 20
#define MAX_SPOT_LIGHTS 20
#define DIRLIGHT_STRENGTH 1.0
#define POINTLIGHT_STRENGTH 1.0
#define SPOTLIGHT_STRENGTH 1.0
#define NORMAL_STRENGTH 0.5
#define blinn true

in vec3 Point;  
in vec3 Normal;  
in vec3 Color;
in vec2 UV;
in vec3 TangentLightPos[MAX_LIGHTS];
in vec3 TangentViewPos;
in vec3 TangentPoint;
  
uniform vec3 viewPos;
uniform Material material;
uniform DirectionLight directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int directionLightCount;
uniform int pointLightCount;
uniform int spotLightCount;
uniform int lightCount;

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 view_direction);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 Point, vec3 view_direction);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 Point, vec3 view_direction);
vec3 CalcNormals(vec3 tangentLightPos);

void main()
{
	// Make sure normals and view_direction is normalized for angle comparisons.
	vec3 normal = normalize(Normal);
	vec3 view_direction = normalize(viewPos - Point);
	
	vec3 result = vec3(0.0f);
	// Calculate directional light(s)
	for (int i = 0; i < directionLightCount; i++)
		result += CalcDirectionLight(directionalLights[i], normal, view_direction) * DIRLIGHT_STRENGTH;
	// Calculate point light(s)
	for (int i = 0; i < pointLightCount; i++)
		result += CalcPointLight(pointLights[i], normal, Point, view_direction) * POINTLIGHT_STRENGTH;
	// Calculate spot light(s)
	for (int i = 0; i < spotLightCount; i++)
		result += CalcSpotLight(spotLights[i], normal, Point, view_direction) * SPOTLIGHT_STRENGTH;
	// Calculate normals
	for (int i = 0; i < lightCount; i++)
		result += CalcNormals(TangentLightPos[i]) * NORMAL_STRENGTH;

	float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));
	if (brightness > 1.0)
		BrightColor = vec4(result, 1.0);
	else
		BrightColor = vec4(0.0, 0.0, 0.0, 1.0);

	// Result output
	FragColor = vec4(result, 1.0);
} 

// calculates the color when using a directional light.
vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 view_direction)
{
	vec3 light_direction = normalize(-light.direction);
	// diffuse shading
	float angle = max(dot(normal, light_direction), 0.0);
	// specular shading
	vec3 reflect_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	vec3 diffuse = light.diffuse * angle * vec3(texture(material.diffuse, UV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));
	return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 Point, vec3 view_direction)
{
	vec3 light_direction = normalize(light.position - Point);
	// diffuse shading
	float angle = max(dot(normal, light_direction), 0.0);
	// specular shading, blinn-pong
	vec3 reflect_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
	if (blinn)
	{
		vec3 halfway_direction = normalize(light_direction + view_direction);
		spec = pow(max(dot(normal, halfway_direction), 0.0), 32.0);
	}
	// attenuation
	float distance = length(light.position - Point);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV)) * attenuation;
	vec3 diffuse = light.diffuse * angle * vec3(texture(material.diffuse, UV)) * attenuation;
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV) * attenuation);

	return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 Point, vec3 view_direction)
{
	vec3 light_direction = normalize(light.position - Point);
	// diffuse shading
	float angle = max(dot(normal, light_direction), 0.0);
	// specular shading
	vec3 reflect_direction = reflect(-light_direction, normal);
	float spec = pow(max(dot(view_direction, reflect_direction), 0.0), material.shininess);
	// attenuation
	float distance = length(light.position - Point);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// spotlight intensity
	float theta = dot(light_direction, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV) * attenuation * intensity);
	vec3 diffuse = light.diffuse * angle * vec3(texture(material.diffuse, UV)) * attenuation * intensity;
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV)) * attenuation * intensity;

	return (ambient + diffuse + specular);
}

// calculates the normal from normal texture (if any)
vec3 CalcNormals(vec3 tangentLightPos)
{
	// obtain normal from normal map in range [0,1]
	vec3 normal = texture(material.normal, UV).rgb;
	// transform normal vector to range [-1,1], normal is in tangent space
	normal = normalize(normal * 2.0 - 1.0);  
	// angle
	vec3 light_direction = normalize(tangentLightPos - TangentPoint);
	float angle = max(dot(light_direction, normal), 0.0);
	// get diffuse color
	vec3 color = texture(material.diffuse, UV).rgb;
	// ambient & diffuse
	vec3 ambient = 0.1 * color;
	vec3 diffuse = 0.5 * color;
	// specular
	vec3 view_direction = normalize(TangentViewPos - TangentPoint);
	vec3 reflect_direction = reflect(-light_direction, normal);
	vec3 halfway_direction = normalize(light_direction + view_direction);
	float specular = pow(max(dot(normal, halfway_direction), 0.0), 32.0) * 0.2;

	return (ambient + diffuse * angle + specular * angle);
}