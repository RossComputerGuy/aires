#version 150 core

in vec4 Color;
in vec3 Texcoord;

out vec4 outColor;

uniform sampler3D tex;

void main() {
	outColor = texture(tex, Texcoord);
}

/* vim:set ft=glsl: */
