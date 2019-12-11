#version 150 core

in vec3 position;
in vec4 color;

out vec4 Color;

uniform mat4 transform;

void main() {
	Color = color;
	gl_Position = (transform * vec4(position, 1.0));
}
