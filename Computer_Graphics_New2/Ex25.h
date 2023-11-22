#pragma once
#include "pch.h"
class Ex25 : protected Examples
{
public:
	Ex25();
	virtual ~Ex25() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	void AnimationUpdate();

	void MakeLightOrbit();

	void Render();
	void RenderLightObj();
	void RenderLightOrbit();


protected:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;

	Model* _cube = nullptr;
	Model* _pyramid = nullptr;
	RGB _objColor = { 0.0f, 1.0f, 0.0f };
	RGB _lightobjColor = { 0.8f, 0.8f, 0.8f };

	Light* _light = nullptr;

	glm::mat4 _objRotMat = glm::mat4(1.0f);
	float rotDeg = 0.0f;
	float rotSpeed = 50.0f;
	bool rotAnim = false;
	bool drawMode = true;

	bool lightRotAnim = false;
	glm::mat4 lightRotMat = glm::mat4(1.0f);
	float lightRotSpeed = 50.0f;

	// Α¶Έν ±Λµµ
	VAO* _orbit = nullptr;
	vector<glm::vec3> _orbitvBuf;

	float _deltaTime;
};

