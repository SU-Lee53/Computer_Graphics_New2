#pragma once
#include "pch.h"


class Ex19 : protected Examples
{
public:
	Ex19();
	virtual ~Ex19() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

	

	void Render();

	void SetOrbit();
	void SetPlanet();

	void RenderOrbit();
	void RenderPlanet();

	void MoveSystem(DIR dir);
	void PlayAnim();
private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);

	// ū �˵� -> �θ� �༺���� ���� ���
	VAO* _bigOrbit = nullptr;
	float _bigOrbitRadius = 3.0f;
	float _bigOrbitVBuf[150];
	float _bigOrbitCBuf[150];

	// ���� �˵� -> �ڽ� �༺���� ���� ���
	VAO* _smallOrbit = nullptr;
	float _smallOrbitRadius = 1.0f;
	float _smallOrbitVBuf[400];
	float _smallOrbitCBuf[400];

	// ��ο� ���� ��ȯ���
	glm::mat4 _orbit1;
	glm::mat4 _orbit2;
	glm::mat4 _orbit3;

	// �༺: ����1, �θ�3, �ڽ�3(Ʈ��ó��)
	// ���� �ϳ� ����� �������� �����ؼ� ����
	Objects* _planet;
	glm::mat4 _scaleMat1 = glm::mat4(1.0f);
	glm::mat4 _scaleMat2 = glm::mat4(1.0f);


	// �� ��ȯ���
	glm::mat4 _ancestorMat = glm::mat4(1.0f);

	glm::mat4 _parentMat1 = glm::mat4(1.0f);
	glm::mat4 _parentMat2 = glm::mat4(1.0f);
	glm::mat4 _parentMat3 = glm::mat4(1.0f);

	glm::mat4 _childMat1 = glm::mat4(1.0f);
	glm::mat4 _childMat2 = glm::mat4(1.0f);
	glm::mat4 _childMat3 = glm::mat4(1.0f);
	
	// ������ ���� -> �˵���ŭ �� �̵�
	glm::mat4 _lastMat1 = glm::mat4(1.0f);
	glm::mat4 _lastMat2 = glm::mat4(1.0f);
	glm::mat4 _lastMat3 = glm::mat4(1.0f);


	glm::mat4 yRot1 = glm::mat4(1.0f);
	float yDeg1 = 0.0f;

	glm::mat4 yRot2 = glm::mat4(1.0f);
	float yDeg2 = 0.0f;
	
	glm::mat4 yRot3 = glm::mat4(1.0f);
	float yDeg3 = 0.0f;


	// ���Ϻ��� ����Ű ��� �÷���
	bool _perspective = true;
	bool _yRotateAnim = false;
	bool _zRotateAnim = false;
	bool _yRotateDirection = false;
	bool _zRotateDirection = false;

	float _yAnimDeg = 0.0f;
	float _zAnimDeg = 0.0f;
	glm::mat4 _yAnimMat = glm::mat4(1.0f);
	glm::mat4 _zAnimMat = glm::mat4(1.0f);

	unsigned int colorLocation;
	unsigned int shaderID;
};



// p / P: ���� ���� / ���� ����
// m / M : �ָ��� �� / ���̾� ��
// w / a / s / d : ���� �������� �� / �� / �� / �Ϸ� �̵�(x��� y�� �� �̵� - ��ü �̵�)
// + / -: ���� �������� �� / �ڷ� �̵�(z�� �� �̵� - ��ü �̵�)
// y / Y : ��ü ��ü���� y������ �� / �� �������� ȸ��(�߾��� ���� y�࿡ ���Ͽ� ȸ��)
// z / Z : �߽��� ���� �����ϰ� �༺, ��, �˵��� z�࿡ ���Ͽ� �� / �� �������� ������ ȸ��
