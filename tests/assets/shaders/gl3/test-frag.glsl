#version 300 es

precision mediump float;

out vec4 fragColor;
in vec3 obj_color;

void main() {
	fragColor = vec4(obj_color, 1.0);
}
