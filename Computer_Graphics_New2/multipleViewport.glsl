#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Color;

out vec3 out_Color;

uniform mat4 model;
uniform mat4 projection1;
uniform mat4 view1;

uniform mat4 projection2;
uniform mat4 view2;

uniform mat4 projection3;
uniform mat4 view3;


void main()
{
	gl_Position = projection1 * view1 * model * vec4(in_Position, 1.0f);
	gl_Position = projection2 * view2 * model * vec4(in_Position, 1.0f);
	gl_Position = projection3 * view3 * model * vec4(in_Position, 1.0f);


	out_Color = in_Color;
}