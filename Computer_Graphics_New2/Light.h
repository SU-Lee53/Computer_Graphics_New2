#pragma once
#include "pch.h"

class Light
{
public:
	Light(glm::vec3 pos, glm::vec3 color, float aIntensity, float dIntensity, unsigned int shaderID);
	~Light();

	void lightTransform(glm::mat4 transfMat);
	void Bind();

	void ChangeLightColor(glm::vec3 lightColor)
	{
		_lightColor = lightColor;
	}
	void ChangeAmbientIntensity(float value) { _ambientIntensity = value; }

	glm::vec3 getLightPos() { return _lightPos; }


protected:
	glm::vec3 _lightColor;
	glm::vec3 _lightPos;
	glm::mat4 _lightMat = glm::mat4(1.0f);

	float _ambientIntensity;
	float _diffuseIntensity;

	unsigned int _shaderID;
};

