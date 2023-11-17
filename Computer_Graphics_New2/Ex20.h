#pragma once
#include "pch.h"


class Ex20 : protected Examples
{
public:
	Ex20();
	virtual ~Ex20() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}


private:
	void PlayCraneAnim();
	void PlayCameraAnim();

	void Render();

	void MakeCrane();
	// �� �κ��� �߾��� ��ķ� ������� -> ȸ���� ��밡��
	// �� �������� ���� �� ������� �׳� ������ zȸ���� ���� ��ĸ� ����
	void SetCraneMatrix();	
	void RenderCrane();
	
	void ResetAll();

private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;

	Objects* _floor = nullptr;
	// 0: �Ʒ���, 1: ����, 2: ���ϴ� ����, 3: ���ϴ� ����
	// 4: �»�� ��, 5: ���� ��
	Objects* _crane[6];


	// ���� ũ���� ��ȯ�� ���� ������

	glm::mat4 _armLeft;
	glm::mat4 _armRight;
	glm::mat4 _armLeft2;
	glm::mat4 _armRight2;

	bool _xMoveAllAnim = false;
	bool _xMoveAllDir = true;
	glm::mat4 _xMoveAll = glm::mat4(1.0f);
	float _xDistAll = 0.0f;

	bool _yRotUpperAnim = false;
	bool _yRotUpperDir = true;
	glm::mat4 _yRotUpper = glm::mat4(1.0f);
	float _yDegUpper = 0.0f;

	bool _yRotBarrelAnim = false;
	bool _yRotBarrelDir = true;
	glm::mat4 _yRotBarrelLeft = glm::mat4(1.0f);
	glm::mat4 _yRotBarrelRight = glm::mat4(1.0f);
	float _yDegBarrelLeft = 0.0f;
	float _yDegBarrelRight = 0.0f;
	
	bool _xMoveDBarrelAnim = false;
	bool _xMoveDBarrelDir = true;
	glm::mat4 _xMoveBarrelLeft = glm::mat4(1.0f);
	glm::mat4 _xMoveBarrelRight = glm::mat4(1.0f);
	float _xDistBarrelLeft = 0.0f;
	float _xDistBarrelRight = 0.0f;

	bool _zRotArmAnim = false;
	bool _zRotArmDir = true;
	glm::mat4 _zRotArmLeft = glm::mat4(1.0f);
	glm::mat4 _zRotArmRight = glm::mat4(1.0f);
	float _zDegArmLeft = 0.0f;
	float _zDegArmRight = 0.0f;

	// ���� ī�޶� ��ȯ�� ���� ������
	float _camXMove = 0.05f;
	float _camZMove = 0.05f;
	float _camXDist = 0.0f;
	float _camZDist = 0.0f;

	float _camYRot = 90.0f + 45.0f;
	float _camYRev = -45.0f;
	bool _camYRevAnim = false;

	// ��ü �ִϸ��̼� ��Ʈ�� �÷���
	bool AnimPlayAll = true;

};

