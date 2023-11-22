# version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_texCoord;

out vec2 out_texCoord;
out vec3 out_fragPos;
out vec3 out_normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;


uniform vec3 customColor;
// 조명 변수는 나중에 추가

void main()
{
	gl_Position = projection * view * model * vec4(in_Position, 1.0f);
	out_texCoord = in_texCoord;
	vec4 normal = model * vec4(in_Normal, 1.0f);
	out_normal = vec3(normal[0], normal[1], normal[2]);
	out_fragPos = vec3(model * vec4(in_Position, 1.0));

	// 아직 조명 추가 X
}