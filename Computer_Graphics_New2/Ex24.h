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

	// 물체 생성 함수
	void MakeStage();
	void MakeRobot();
	void MakeObstacle();

	// 물체 렌더 함수
	void RenderStage();
	void RenderRobot();
	void RenderObstacle();

	// 애니매이션
	void OpenStage();
	void RobotJump();
	void RobotWalk();
	void RobotWalkAnim();
	void PlayCameraAnim();

	// 충돌 -> 바닥 평면에서의 단순 겹침 판정만 하는 함수를 분리
	// 이유 -> 바닥에 있을때랑 점프해서 공중에 있을때 판정이 다름
	bool CheckCollision();
	bool CheckCollisionBtwHitbox(HITBOX h1, HITBOX h2);
	HITBOX GetRobotHitboxXZ();


private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;


	// 0, 1 -> 왼쪽문, 오른쪽문 
	// 2 -> 위
	// 3, 4, 5 -> 왼쪽, 오른쪽, 뒤
	// 6, 7 -> 아래 1, 아래 2
	Objects* _stage[8];
	glm::mat4 _stageMat[8];
	float _stageOpenDeg = 0.0f;

	// 로봇-> 0,1: 다리 왼쪽 오른쪽, 2: 몸통, 3,4: 팔 왼쪽, 오른쪽, 5: 머리, 6: 코
	Objects* _robot[7];
	HITBOX _rHitbox;

	// 장애물
	// Ex24에서 객체 7개추가
	// Π 형애 장애물 육면체 3개
	// 모서리 원기둥 충돌처리용 육면체 4개
	Objects* _obstacle[10];
	HITBOX _oHitbox[10];
	glm::mat4 _obstacleMat[10];


	// 문을 열고 닫을때 쓸 변수들
	glm::mat4 _openLeft = glm::mat4(1.0f);
	glm::mat4 _openRight = glm::mat4(1.0f);
	float _doorDeg = 0.0f;
	float _doorSpeed = 60.0f;
	bool _doorAnim = false;
	bool _doorOpen = false;

	// 로봇의 이동 행렬
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

	// 로봇 애니매이션 행렬
	glm::mat4 leftLeg = glm::mat4(1.0f);
	glm::mat4 rightLeg = glm::mat4(1.0f);
	glm::mat4 leftArm = glm::mat4(1.0f);
	glm::mat4 rightArm = glm::mat4(1.0f);
	float swingSpeed = 500.0f;
	float walk = 0.0f;
	float walkDeg = 0.0f;
	float _maxWalkDeg = 40.0f;


	// 카메라 변환
	float _camMoveDistZ = 0.0f;
	float _camMoveDistX = 0.0f;
	float _camRotateDeg = 0.0f;
	float _camMoveSpeed = 0.2f;
	float _camRotateSpeed = 50.0f;
	bool _camRotatePlay = false;
	bool _camRotateDir = true;


};


