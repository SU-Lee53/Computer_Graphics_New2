#pragma once
#include "pch.h"



class Ex26 : protected Examples
{
public:
	Ex26();
	virtual ~Ex26() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	void Render();
	  
	void AnimUpdate();

	void MakePlanet();
	void RenderPlanet();

	void RenderLightObj();

private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;

	Model* _sphere = nullptr;
	RGB _objColor = { 0.0f, 1.0f, 0.0f };
	RGB _lightobjColor = { 0.8f, 0.8f, 0.8f };

	Light* _light = nullptr;

	// 행성별 행렬
	glm::mat4 _planet1 = glm::mat4(1.0f);
	glm::mat4 _planet2 = glm::mat4(1.0f);
	glm::mat4 _planet3 = glm::mat4(1.0f);

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

	float _deltaTime;
};

