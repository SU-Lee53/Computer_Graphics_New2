# version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_texCoord;

out vec2 out_texCoord;
out vec3 out_normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform vec4 customColor;
// ���� ������ ���߿� �߰�

void main()
{
	gl_Position = projection * view * model * vec4(in_Position, 1.0f);
	out_texCoord = in_texCoord;
	out_normal = in_Normal;

	// ���� ���� �߰� X
}