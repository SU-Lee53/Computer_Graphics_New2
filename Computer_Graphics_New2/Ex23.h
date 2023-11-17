#pragma once
#include "pch.h"

enum PlaneIndex
{
	RIGHT = 0,
	LEFT,
	UP,
	FRONT,
	BACK,
	BOTTOMLEFT,
	BOTTOMRIGHT
};

enum BallState
{
	BS_BOUNCE = 0,
	BS_FALLING
};

enum CubeState
{
	CS_MOVING,
	CS_FALLING
};

// 육면체 AABB -> 2차원 충돌로 대체가능
struct AABB
{
	float left = 0.0f;
	float top = 0.0f;
	float right = 0.0f;
	float bottom = 0.0f;
};

class Ex23 : protected Examples
{
public:
	Ex23();
	virtual ~Ex23() override;

	virtual void InitEx() override;

	virtual void drawScene() override;
	virtual void Reshape(int w, int h) override;

	virtual void MouseUpdate() override;
	virtual void KeyboardUpdate() override;
	virtual void MotionUpdate() override;
	virtual void SpecialKeyUpdate() override {}

	void Render();
	
	// 물체 생성 함수
	void MakeStage();
	void MakeBall();
	void MakeCube();

	// 물체 렌더 함수
	void RenderStage();
	void RenderBall();
	void RenderCube();

	// 애니메이션 함수
	void RotateScreenAnim();
	void BallMoveAnim();
	void OpenDoorAnim();

	// 육면체 회전
	void RotateCube(float dx);

	// 큐브 이동
	void CubeMove();

	// 공과 평면의 충돌체크
	void CheckCollision();
	bool isIntersect(glm::vec3& center, float radius, glm::vec3& normal, glm::vec3& pointOnPlane);

	// 육면체와 평면의 충돌체크
	bool isIntersectBtwCube(AABB bound);


	// 유틸
	void NormalUpdate(PlaneIndex index, glm::mat4 Matrix);
	void CubeAABBUpdate();


private:
	Projection* _projection;
	Camera* _camera;
	glm::mat4 _worldMat = glm::mat4(1.0);
	unsigned int _shaderID;


	// 무대-> 0: 오른쪽, 1: 왼쪽, 2: 위, 3: 뒤, 4,5: 아래 문 왼쪽/오른쪽
	struct planeInfo
	{
		Objects* planeObj = nullptr;
		glm::mat4 moveMat = glm::mat4(1.0f);
		glm::mat4 planeMat = glm::mat4(1.0f);
		RGB planeColor = { 0.0f, 0.0, 0.0f };
		glm::vec3 planeNormalOrigin = glm::vec3(1.0f);
		glm::vec3 pointOnPlaneOrigin = glm::vec3(1.0f);
		glm::vec3 planeNormal = glm::vec3(1.0f);
		glm::vec3 pointOnPlane = glm::vec3(1.0f);
	};


	vector<planeInfo> _planeList;
	glm::mat4 _planeRotMat = glm::mat4(1.0f);
	float _planeRotDeg = 0.0f;


	// 아래 바닥문 열기
	glm::mat4 _openLeft = glm::mat4(1.0f);
	glm::mat4 _openRight = glm::mat4(1.0f);
	bool _openDoorPlay = false;
	bool _doorOpen = false;
	float _openDegree = 0.0f;
	float _openSpeed = 200.0f;


	// 공
	struct BallInfo
	{
		Objects* ballObj = nullptr;
		glm::mat4 ballMat = glm::mat4(1.0f);
		glm::vec3 dirVector = { 0.0, 0.0, 0.0 };
		glm::vec3 posVector = { 0.0f, 0.0f, 0.0f };
		float ballFallingSpeed = 0.0f;
	};

	vector<BallInfo> _ballList;
	RGB _ballColor = { 0.0,0.0,1.0 };
	float _ballRadius = 0.5f;
	float _ballSpeed = 5.0f;
	BallState _ballState = BS_BOUNCE;



	// 바닥의 육면체
	struct CubeInfo
	{
		Objects* cubeObj = nullptr;
		glm::mat4 cubeMat = glm::mat4(1.0f);
		glm::vec3 dirVector = { 0.0, 0.0, 0.0 };
		glm::vec3 posVector = { 0.0f, 0.0f, 0.0f };
		float cubeSize = 0.0f;
		float cubeMovingSpeed = 0.0f;
		AABB cubeAABB = { 0.0, 0.0, 0.0, 0.0 };
		float cubeFallingSpeed = 0.0f;
		float cubeWeight = 0.0f;
	};

	vector<CubeInfo> _cubeList;
	RGB _cubeColor = { 1.0f, 0.0f, 0.0f };
	CubeState _cubeState = CS_MOVING;

	glm::vec3 prevDir;
	float _gravity = 9.8f;
	glm::vec3 _gravityVector = glm::vec3(0.0f, -1.0f, 0.0f);

	float _rotation = 0.0f;
	bool _rotPlay = false;
	bool _rotDir = false;

	Coord _mousePrevPos = { 0.0f, 0.0f, 0.0f };
	float _deltaTime;
};

