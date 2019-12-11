#version 150 core

in vec3 position;
in vec4 color;

out vec4 vert_color;

void main() {
	vert_color = color;
	gl_Position = vec4(position, 1.0);
}
