#pragma once
#include "pch.h"

struct HITBOX
{
	float left;
	float top;
	float right;
	float bottom;
	float front;
	float rear;
};

class Ex24 : protected Examples
{
public:
	Ex24();
	virtual ~Ex24() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override {}
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override {}
	virtual void SpecialKeyUpdate() override {}

private:
	void Render();
	void Reset();

	// ��ü ���� �Լ�
	void MakeStage();
	void MakeRobot();
	void MakeObstacle();

	// ��ü ���� �Լ�
	void RenderStage();
	void RenderRobot();
	void RenderObstacle();

	// �ִϸ��̼�
	void OpenStage();
	void RobotJump();
	void RobotWalk();
	void RobotWalkAnim();
	void PlayCameraAnim();

	// �浹 -> �ٴ� ��鿡���� �ܼ� ��ħ ������ �ϴ� �Լ��� �и�
	// ���� -> �ٴڿ� �������� �����ؼ� ���߿� ������ ������ �ٸ�
	bool CheckCollision();
	bool CheckCollisionBtwHitbox(HITBOX h1, HITBOX h2);
	HITBOX GetRobotHitboxXZ();


private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;


	// 0, 1 -> ���ʹ�, �����ʹ� 
	// 2 -> ��
	// 3, 4, 5 -> ����, ������, ��
	// 6, 7 -> �Ʒ� 1, �Ʒ� 2
	Objects* _stage[8];
	glm::mat4 _stageMat[8];
	float _stageOpenDeg = 0.0f;

	// �κ�-> 0,1: �ٸ� ���� ������, 2: ����, 3,4: �� ����, ������, 5: �Ӹ�, 6: ��
	Objects* _robot[7];
	HITBOX _rHitbox;

	// ��ֹ�
	// Ex24���� ��ü 7���߰�
	// �� ���� ��ֹ� ����ü 3��
	// �𼭸� ����� �浹ó���� ����ü 4��
	Objects* _obstacle[10];
	HITBOX _oHitbox[10];
	glm::mat4 _obstacleMat[10];


	// ���� ���� ������ �� ������
	glm::mat4 _openLeft = glm::mat4(1.0f);
	glm::mat4 _openRight = glm::mat4(1.0f);
	float _doorDeg = 0.0f;
	float _doorSpeed = 60.0f;
	bool _doorAnim = false;
	bool _doorOpen = false;

	// �κ��� �̵� ���
	glm::mat4 _robotMoveX = glm::mat4(1.0f);
	glm::mat4 _robotMoveY = glm::mat4(1.0f);
	glm::mat4 _robotMoveZ = glm::mat4(1.0f);
	glm::mat4 _robotFace = glm::mat4(1.0f);
	DIR _direction = DIR_NONE;
	bool walkPlay = false;
	float _xMoveDist = 0.0f;
	float _yMoveDist = 0.0f;
	float _zMoveDist = 0.0f;
	float _mvSpeed = 5.0f;
	float _jumpSpeed = 5.0f;
	bool isJumped = false;
	bool jump = false;

	// �κ� �ִϸ��̼� ���
	glm::mat4 leftLeg = glm::mat4(1.0f);
	glm::mat4 rightLeg = glm::mat4(1.0f);
	glm::mat4 leftArm = glm::mat4(1.0f);
	glm::mat4 rightArm = glm::mat4(1.0f);
	float swingSpeed = 500.0f;
	float walk = 0.0f;
	float walkDeg = 0.0f;
	float _maxWalkDeg = 40.0f;


	// ī�޶� ��ȯ
	float _camMoveDistZ = 0.0f;
	float _camMoveDistX = 0.0f;
	float _camRotateDeg = 0.0f;
	float _camMoveSpeed = 0.2f;
	float _camRotateSpeed = 50.0f;
	bool _camRotatePlay = false;
	bool _camRotateDir = true;


};


