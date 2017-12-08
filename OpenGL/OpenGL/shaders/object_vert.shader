#version 450 core
layout (location = 0) in vec3 aPoints;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec3 aColors;
layout (location = 3) in vec2 aUVs;
layout (location = 4) in vec3 aTangent;
layout (location = 5) in vec3 aBitangent;

#define MAX_LIGHTS 20

out vec3 Point;
out vec3 Normal;
out vec3 Color;
out vec2 UV;
out vec3 TangentLightPos[MAX_LIGHTS];
out vec3 TangentViewPos;
out vec3 TangentPoint;

uniform vec2 scale;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int lightCount;
uniform vec3 lightPositions[MAX_LIGHTS];
uniform vec3 viewPos;

void main()
{
    Point = vec3(model * vec4(aPoints, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormals; 
	Color = aColors;
    
	UV = vec2(aUVs.x * scale.x, aUVs.y * scale.y);
    
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 T = normalize(normalMatrix * aTangent);
	vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0)));
	vec3 N = normalize(normalMatrix * aNormals);

	mat3 TBN = transpose(mat3(T, B, N));
	for (int i = 0; i < lightCount; i++)
		TangentLightPos[i] = TBN * lightPositions[i];
	TangentViewPos = TBN * viewPos;
	TangentPoint = TBN * Point;

    gl_Position = projection * view * vec4(Point, 1.0);
}