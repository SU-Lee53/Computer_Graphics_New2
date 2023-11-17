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

	// 큰 궤도 -> 부모 행성들이 도는 경로
	VAO* _bigOrbit = nullptr;
	float _bigOrbitRadius = 3.0f;
	float _bigOrbitVBuf[150];
	float _bigOrbitCBuf[150];

	// 작은 궤도 -> 자식 행성들이 도는 경로
	VAO* _smallOrbit = nullptr;
	float _smallOrbitRadius = 1.0f;
	float _smallOrbitVBuf[400];
	float _smallOrbitCBuf[400];

	// 경로에 대한 변환행렬
	glm::mat4 _orbit1;
	glm::mat4 _orbit2;
	glm::mat4 _orbit3;

	// 행성: 조상1, 부모3, 자식3(트리처럼)
	// 조상 하나 만들고 나머지는 신축해서 만듬
	Objects* _planet;
	glm::mat4 _scaleMat1 = glm::mat4(1.0f);
	glm::mat4 _scaleMat2 = glm::mat4(1.0f);


	// 헹성 변환행렬
	glm::mat4 _ancestorMat = glm::mat4(1.0f);

	glm::mat4 _parentMat1 = glm::mat4(1.0f);
	glm::mat4 _parentMat2 = glm::mat4(1.0f);
	glm::mat4 _parentMat3 = glm::mat4(1.0f);

	glm::mat4 _childMat1 = glm::mat4(1.0f);
	glm::mat4 _childMat2 = glm::mat4(1.0f);
	glm::mat4 _childMat3 = glm::mat4(1.0f);
	
	// 공전의 공전 -> 궤도만큼 더 이동
	glm::mat4 _lastMat1 = glm::mat4(1.0f);
	glm::mat4 _lastMat2 = glm::mat4(1.0f);
	glm::mat4 _lastMat3 = glm::mat4(1.0f);


	glm::mat4 yRot1 = glm::mat4(1.0f);
	float yDeg1 = 0.0f;

	glm::mat4 yRot2 = glm::mat4(1.0f);
	float yDeg2 = 0.0f;
	
	glm::mat4 yRot3 = glm::mat4(1.0f);
	float yDeg3 = 0.0f;


	// 이하부터 조작키 토글 플래그
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



// p / P: 직각 투영 / 원근 투영
// m / M : 솔리드 모델 / 와이어 모델
// w / a / s / d : 위의 도형들을 좌 / 우 / 상 / 하로 이동(x축과 y축 값 이동 - 객체 이동)
// + / -: 위의 도형들을 앞 / 뒤로 이동(z축 값 이동 - 객체 이동)
// y / Y : 전체 객체들을 y축으로 양 / 음 방향으로 회전(중앙의 구의 y축에 대하여 회전)
// z / Z : 중심의 구를 제외하고 행성, 달, 궤도가 z축에 대하여 양 / 음 방향으로 일제히 회전
