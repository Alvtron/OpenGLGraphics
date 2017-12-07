#version 450

layout(location = 0) in vec3 aPoints;
layout(location = 0) out vec3 vertex_pos;

void main() {
	vertex_pos = aPoints;
	gl_Position = vec4(aPoints, 1.0);
}