#version 150 core

in vec3 position;
in vec4 color;
in vec2 texcoord;

out vec3 Color;
out vec3 Texcoord;

uniform mat4 camera;
uniform mat4 transform;

void main() {
	Color = color;
	Texcoord = texcoord;
	gl_Position = camera * transform * vec4(position, 1.0);
}

/* vim:set ft=glsl: */
