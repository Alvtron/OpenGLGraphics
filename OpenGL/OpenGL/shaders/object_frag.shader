#version 450 core
out vec4 FragColor;

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

#define MAX_POINT_LIGHTS 20
#define DIRLIGHT_STRENGTH 0.8
#define POINTLIGHT_STRENGTH 0.8
#define NORMAL_STRENGTH 0.9
#define blinn true

in vec3 Point;  
in vec3 Normal;  
in vec3 Color;
in vec2 UV;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentPoint;
  
uniform int pointLightCount;
uniform int directionLightCount;
uniform vec3 viewPos;
uniform DirectionLight directionLight;
uniform Material material;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 Point, vec3 viewDir);
vec3 CalcNormals();

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - Point);
	vec3 result = vec3(0.0f);
	result += CalcDirectionLight(directionLight, normal, viewDir) * DIRLIGHT_STRENGTH;
	for(int i = 0; i < pointLightCount; i++)
        result += CalcPointLight(pointLights[i], normal, Point, viewDir) * POINTLIGHT_STRENGTH;

	result += CalcNormals() * NORMAL_STRENGTH;

	FragColor = vec4(result, 1.0);
} 

// calculates the color when using a directional light.
vec3 CalcDirectionLight(DirectionLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflect_direction = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflect_direction), 0.0), material.shininess);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 Point, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - Point);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading, blinn-pong
	vec3 reflect_direction = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflect_direction), 0.0), material.shininess);
	if (blinn)
	{
		vec3 halfwayDir = normalize(lightDir + viewDir);
		spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	}
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
	return (ambient + diffuse + specular);
}

vec3 CalcNormals()
{
	// obtain normal from normal map in range [0,1]
	vec3 normal = texture(material.normal, UV).rgb;
	// transform normal vector to range [-1,1]
	// this normal is in tangent space
	normal = normalize(normal * 2.0 - 1.0);  
	// get diffuse color
	vec3 color = texture(material.diffuse, UV).rgb;
	// ambient
	vec3 ambient = 0.1 * color;
	// diffuse
	vec3 lightDir = normalize(TangentLightPos - TangentPoint);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;
	// specular
	vec3 viewDir = normalize(TangentViewPos - TangentPoint);
	vec3 reflect_direction = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

	vec3 specular = vec3(0.2) * spec;
	return (ambient + 0.5*diffuse + specular);
}