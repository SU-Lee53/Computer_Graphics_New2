#version 330 core

in vec2 out_texCoord;
in vec3 out_normal;
in vec3 out_fragPos;

out vec4 fragColor;

uniform vec3 customColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform float ambientLight;

void main()
{
	vec3 ambient = ambientLight * lightColor;

	vec3 normalVector = normalize(out_normal);
	vec3 lightDir = normalize(lightPos - out_fragPos);
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);
	vec3 diffuse = diffuseLight * lightColor;

	int shiness = 1024;
	vec3 viewDir = normalize(viewPos - out_fragPos);
	vec3 reflectDir = reflect(-lightDir, normalVector);
	float specularLight = max(dot(viewDir, reflectDir), 0.0);
	specularLight = pow(specularLight, shiness);
	vec3 specular = specularLight * lightColor;

	vec3 result = (ambient + diffuse + specular) * customColor;

	fragColor = vec4(result, 1.0);
}
