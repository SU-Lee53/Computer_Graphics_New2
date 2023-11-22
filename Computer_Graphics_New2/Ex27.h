#pragma once
#include "pch.h"

class Ex27 : protected Examples
{
public:
	Ex27();
	virtual ~Ex27() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	void AnimUpdate();

	void Render();

	void RenderCrane();
	void RenderLightObj();

private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;

	Model* _floor = nullptr;
	Model* _upper = nullptr;
	Model* _lower = nullptr;
	Model* _lightObj = nullptr;
	RGB _floorColor = { 0.0f, 1.0f, 0.0f };
	RGB _lowerColor = { 0.0f, 1.0f, 0.0f };
	RGB _upperColor = { 0.0f, 1.0f, 0.0f };
	RGB _lightobjColor = { 0.8f, 0.8f, 0.8f };

	Light* _light = nullptr;

	bool craneMoveSwitch = false;
	glm::mat4 craneMoveMat = glm::mat4(1.0f);
	float craneMov = 0.0f;
	float paramDeg = 0.0f;

	// 조명 애니메이션
	bool lightRotAnim = false;
	glm::mat4 lightRotMat = glm::mat4(1.0f);
	float lightRotSpeed = 40.0f;
	bool lightRotDir = true;

	enum LIGHT_COLOR
	{
		WHITE = 0,
		RED,
		GREEN,
		BLUE
	};

	int lightColorSwitch = 0;
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	bool ambientSwitch = true;

	float _camXMove = 1.0f;
	float _camZMove = 1.0f;
	float _camXDist = 1.0f;
	float _camZDist = 1.0f;

	float _camYRot = 0.0f;
	float _camYRev = 0.0f;
	bool _camYRevAnim = false;

	float _deltaTime;
};

