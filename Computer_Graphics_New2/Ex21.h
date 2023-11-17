#pragma once
#include "pch.h"


class Ex21 : protected Examples
{
public:
	Ex21();
	virtual ~Ex21() override;

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
	
	void SetCraneMatrix();
	void RenderCrane();

	void ResetAll();

	void DrawViewport1();
	void DrawViewport2();
	void DrawViewport3();


private:
	// 원근투영
	Projection* _projection1;
	Camera* _camera1;

	// xz 직각투영
	Projection* _projection2;
	Camera* _camera2;

	// xy 직각투영
	Projection* _projection3;
	Camera* _camera3;






	// 이하는 21번에서는 신경쓰지 말자

	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;

	Objects* _floor = nullptr;
	// 0: 아랫몸, 1: 윗몸, 2: 좌하단 포신, 3: 우하단 포신
	// 4: 좌상단 팔, 5: 우상단 팔
	Objects* _crane[6];


	// 이하 크레인 변환을 위한 변수들

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

	// 이하 카메라 변환을 위한 변수들
	float _camXMove = 0.05f;
	float _camZMove = 0.05f;
	float _camXDist = 0.0f;
	float _camZDist = 0.0f;

	float _camYRot = 90.0f + 45.0f;
	float _camYRot2 = 180.0f;
	float _camYRot3 = 180.0f;
	float _camYRev = -45.0f;
	float _camYRev2 = 0.0f;
	float _camYRev3 = 0.0f;
	bool _camYRevAnim = false;

	// 전체 애니메이션 컨트롤 플래그
	bool AnimPlayAll = true;

};



