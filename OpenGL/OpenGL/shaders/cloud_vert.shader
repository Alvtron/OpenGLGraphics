#version 450 core

layout(location = 0) in vec3 aPoints;
layout(location = 0) out vec3 vertex_position;

void main() {
	vertex_position = aPoints;
	gl_Position = vec4(aPoints, 1.0);
}