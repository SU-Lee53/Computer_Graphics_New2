#include "pch.h"
#include "Light.h"

Light::Light(glm::vec3 pos, glm::vec3 color, float aIntensity, float dIntensity, unsigned int shaderID)
	:_lightColor(color), _ambientIntensity(aIntensity), _diffuseIntensity(dIntensity), _shaderID(shaderID)
{
	_lightPos = _lightMat * glm::vec4(pos, 1.0f);
}

Light::~Light()
{
}

void Light::lightTransform(glm::mat4 transfMat)
{
	_lightMat = glm::mat4(1.0f) * transfMat;
	_lightPos = _lightMat * glm::vec4(_lightPos, 1.0f);
}

void Light::Bind()
{
	unsigned int posLoc = glGetUniformLocation(_shaderID, "lightPos");
	unsigned int colorLoc = glGetUniformLocation(_shaderID, "lightColor");
	unsigned int ambientLoc = glGetUniformLocation(_shaderID, "ambientLight");

	glUniform3f(posLoc, _lightPos[0], _lightPos[1], _lightPos[2]);
	glUniform3f(colorLoc, _lightColor[0], _lightColor[1], _lightColor[2]);
	glUniform1f(ambientLoc, _ambientIntensity);
}
