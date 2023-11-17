#version 330 core

uniform vec3 uniformColor;
out vec4 fragColor;

void main()
{
	fragColor = vec4(uniformColor, 1.0);
}
