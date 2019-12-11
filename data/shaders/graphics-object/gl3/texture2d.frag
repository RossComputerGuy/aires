#version 150 core

in vec4 Color;
in vec3 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main() {
	outColor = texture(tex, vec2(Texcoord.x, Texcoord.y));
}

/* vim:set ft=glsl: */
