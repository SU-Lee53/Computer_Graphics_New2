#version 330 core

in vec2 in_texCoord;
in vec3 in_normal;

out vec4 fragColor;

uniform vec4 customColor;

void main()
{
	fragColor = vec4(in_texCoord, 0.0, 0.0);
}
