#include "pch.h"
#include "Ex24.h"

Ex24::Ex24()
{
	InitEx();
}

Ex24::~Ex24()
{
}

void Ex24::InitEx()
{
	srand(time(0));
	cout << "육면체를 사용하여 무대를 그리고, 키보드를 누르면 무대의 앞면이 좌우로 슬라이딩하여 열린다." << endl;
	cout << "무대는 육면을 가지고 있다.각각 다른색으로 구현한다." << endl;
	cout << "	o / O: 앞면이 좌우로 열린다." << endl;
	cout << "바닥에 육면체의 장애물이 랜덤한 위치에 3개 있다." << endl;
	cout << "무대 위에는 로봇이 팔을 흔들며 걷고 있다." << endl;
	cout << "로봇은 머리, 몸통, 양 팔, 양 다리가 있고 팔, 다리를 흔들며 걷는다." << endl;
	cout << "머리의 앞면에 코를 붙이고(앞뒤 구분), 양팔과 양 다리는 다른색을 사용한다.(방향 구분)" << endl;
	cout << "키보드 명령어를 사용하여 로봇은 이동 방향을 바꿔서 움직인다." << endl;
	cout << "	w / a / s / d: 로봇이 앞 / 뒤 / 좌 / 우 방향으로 이동 방향을 바꿔서 걷는다.가장자리에 도달하면 로봇은 뒤로 돌아 다시 걷는다." << endl;
	cout << "	+ / -: 걷는 속도가 빨라지거나 / 느려진다.속도가 바뀔 때 걷는 다리의 각도가 늘어나거나 / 줄어든다." << endl;
	cout << "	j : 로봇이 제자리에서 점프한다.장애물 위로 점프하여 올라가고 내려갈 수 있다." << endl;
	cout << "	i : 모든 변환을 리셋하고 다시 시작" << endl;
	cout << "카메라 설정 : 키보드 명령으로 카메라 이동" << endl;
	cout << "	z / Z : 앞뒤로 이동" << endl;
	cout << "	x / X : 좌우로 이동" << endl;
	cout << "	y / Y : 카메라가 현재 위치에서 화면 중심 y축을 기준으로 공전" << endl;

	for (int i = 0; i < 6; i++)
	{
		_stage[i] = nullptr;
	}

	_camera = new Camera(glm::vec3(0.0, 4.0, 10.0), glm::vec3(0.0, 4.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);

}

void Ex24::drawScene()
{
	_shaderID = GET_SINGLE(Core).GetShaderID();
	glUseProgram(_shaderID);

	_camera->Bind(_shaderID);
	_projection->Bind(_shaderID);
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);

	KeyboardUpdate();

	if (_stage[0] != nullptr)
	{
		OpenStage();
		RobotJump();
		RobotWalk();
		RobotWalkAnim();
		PlayCameraAnim();
	}

	Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Ex24::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex24::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();
	if (ks == nullptr)
	{
		return;
	}

	switch (ks->key)
	{
	case 'o':
		if (!_doorAnim)
			_doorAnim = true;

		_doorOpen = true;
		break;

	case 'O':
		if (!_doorAnim)
			_doorAnim = true;

		_doorOpen = false;
		break;

	case 'w':
		walkPlay = true;
		_direction = DIR_FRONT;
		break;

	case 's':
		walkPlay = true;
		_direction = DIR_BACK;
		break;

	case 'd':
		walkPlay = true;
		_direction = DIR_RIGHT;
		break;

	case 'a':
		walkPlay = true;
		_direction = DIR_LEFT;
		break;

	case 'r':
		walkPlay = true;
		_direction = DIR_NONE;
		break;

	case 'j':
		if (!isJumped)
		{
			isJumped = true;
			jump = true;
		}
		break;

	case '+':
		_mvSpeed += 0.0005f;
		_maxWalkDeg += 3.0f;
		break;

	case '-':
		_mvSpeed -= 0.0005f;
		_maxWalkDeg -= 3.0f;
		break;

	case 'z':
		_camera->CameraMove(glm::vec3(0.0f, 0.0f, _camMoveSpeed));
		_camMoveDistZ += _camMoveSpeed;
		break;

	case 'Z':
		_camera->CameraMove(glm::vec3(0.0f, 0.0f, -(_camMoveSpeed)));
		_camMoveDistZ -= _camMoveSpeed;
		break;

	case 'x':
		_camera->CameraMove(glm::vec3(_camMoveSpeed, 0.0f, 0.0f));
		_camMoveDistX += _camMoveSpeed;
		break;

	case 'X':
		_camera->CameraMove(glm::vec3(-(_camMoveSpeed), 0.0f, 0.0f));
		_camMoveDistX -= _camMoveSpeed;
		break;

	case 'y':
		if (!_camRotatePlay)
		{
			_camRotatePlay = true;
			_camRotateDir = true;
		}
		else
			_camRotatePlay = false;
		break;

	case 'Y':
		if (!_camRotatePlay)
		{
			_camRotatePlay = true;
			_camRotateDir = false;
		}
		else
			_camRotatePlay = false;
		break;

	case 'i':
		Reset();
		break;

	}





	delete ks;
}

void Ex24::Render()
{
	if (_stage[0] == nullptr)
	{
		MakeStage();
		MakeRobot();
		MakeObstacle();
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	RenderStage();
	RenderObstacle();
	RenderRobot();

}

void Ex24::Reset()
{
	for (int i = 0; i < 3; i++)
	{
		delete _obstacle[i];
	}
	MakeObstacle();

	_robotMoveX = glm::mat4(1.0f);
	_robotMoveY = glm::mat4(1.0f);
	_robotMoveZ = glm::mat4(1.0f);
	_robotFace = glm::mat4(1.0f);
	_direction = DIR_NONE;

	_xMoveDist = 0.0f;
	_yMoveDist = 0.0f;
	_zMoveDist = 0.0f;

	leftLeg = glm::mat4(1.0f);
	rightLeg = glm::mat4(1.0f);
	leftArm = glm::mat4(1.0f);
	rightArm = glm::mat4(1.0f);

	_camera->CameraMove(glm::vec3(-(_camMoveDistX), 0.0f, -(_camMoveDistZ)));
	_camMoveDistZ = 0.0f;
	_camMoveDistX = 0.0f;
	_camRotateDeg = 0.0f;


	_camera->CameraRevolution(-(_camRotateDeg), Y_AXIS);
	_camRotateDeg = 0.0f;
	_camRotatePlay = false;
}

void Ex24::MakeStage()
{
	glm::mat4 scale, rot, move;

	// 문은 평면을 만들고 신축으로 크기를 조절한 다음 회전해서 만듬
	_stage[0] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 1.0f, 1.0f));
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, X_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-2.0f, 4.0f, 4.0f));
	_stageMat[0] = move * rot * scale;
	_stage[0]->ChangeColor({ 1.0f,0.3f,0.0f });

	_stage[1] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 1.0f, 1.0f));
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, X_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(2.0f, 4.0f, 4.0f));
	_stageMat[1] = move * rot * scale;
	_stage[1]->ChangeColor({ 1.0f,0.3f,0.0f });

	_stage[2] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 0.5f, INDEXED);
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(16.0f, 1.0f, 10.0f));
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 10.0f, 0.0f));
	_stageMat[2] = move * scale;
	_stage[2]->ChangeColor({ 1.0f,1.0f,0.0f });

	//	_stage[3] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	//	rot = GET_SINGLE(TransformManager).GetRotateMatrix(180.0f, Z_AXIS);
	//	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
	//	_stageMat[3] = move * rot;
	//	_stage[3]->ChangeColor({ 0.0f,1.0f,1.0f });

	_stage[3] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 5.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, Z_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-8.0f, 5.0f, 0.0f));
	_stageMat[3] = move * rot;
	_stage[3]->ChangeColor({ 1.0f,0.0f,1.0f });

	_stage[4] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 5.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(-90.0f, Z_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(8.0f, 5.0f, 0.0f));
	_stageMat[4] = move * rot;
	_stage[4]->ChangeColor({ 0.0f,1.0f,0.0f });

	_stage[5] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 0.5f, INDEXED);
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(16.0f, 1.0f, 10.0f));
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(-90.0f, X_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 5.0f, -5.0f));
	_stageMat[5] = move * rot * scale;
	_stage[5]->ChangeColor({ 0.0f,0.0f,1.0f });
	

	// 바닥면의 이동행렬은 렌더링시 만듬

	_stage[6] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 0.5f, INDEXED);
	_stageMat[6] = GET_SINGLE(TransformManager).GetRotateMatrix(180.0f, Z_AXIS);
	_stage[6]->ChangeColor({ 1.0f, 1.0f, 1.0f });

	_stage[7] = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 0.5f, INDEXED);
	_stageMat[7] = glm::mat4(1.0f);
	_stage[7]->ChangeColor({ 0.0f, 0.0f, 0.0f });


}

void Ex24::MakeRobot()
{
	// 다리
	_robot[0] = new Objects(0.1f, 0.1f, 0.3f, -0.1f, 0.0f, 0.5f);
	_robot[0]->ChangeColor({ 1.0f, 0.0f, 0.0f });
	_robot[1] = new Objects(-0.3f, 0.1f, -0.1f, -0.1f, 0.0f, 0.5f);
	_robot[1]->ChangeColor({ 1.0f, 1.0f, 0.5f });

	// 몸통
	_robot[2] = new Objects(-0.3f, 0.1f, 0.3f, -0.1f, 0.5f, 1.3f);
	_robot[2]->ChangeColor({ 0.0f, 0.3f, 0.5f });

	// 팔
	_robot[3] = new Objects(-0.5f, 0.1f, -0.3f, -0.1f, 0.7f, 1.3f);
	_robot[3]->ChangeColor({ 1.0f, 0.0f, 0.0f });
	_robot[4] = new Objects(0.3f, 0.1f, 0.5f, -0.1f, 0.7f, 1.3f);
	_robot[4]->ChangeColor({ 1.0f, 1.0f, 0.0f });

	// 머리, 코
	_robot[5] = new Objects(-0.2f, 0.2f, 0.2f, -0.2f, 1.3f, 1.7f);
	_robot[5]->ChangeColor({ 0.0f, 0.6f, 0.5f });
	_robot[6] = new Objects(-0.05f, 0.2f, 0.05f, 0.3f, 1.4f, 1.45f);
	_robot[6]->ChangeColor({ 1.0f, 0.0f, 0.0f });
}

void Ex24::MakeObstacle()
{
	Coord pos1, pos2, pos3;

	pos1.x = static_cast<float>((rand() % 13) - 6) + 0.5f;
	pos1.y = 0.5f;
	pos1.z = static_cast<float>((rand() % 9) - 4) + 0.5f;
	
	pos2.x = static_cast<float>((rand() % 13) - 6) + 0.5f;
	pos2.y = 0.5f;
	pos2.z = static_cast<float>((rand() % 9) - 4) + 0.5f;
	
	pos3.x = static_cast<float>((rand() % 13) - 6) + 0.5f;
	pos3.y = 0.5f;
	pos3.z = static_cast<float>((rand() % 9) - 4) + 0.5f;

	// 4, 5번에는 Π 장애물의 기둥부
	Coord pos4, pos5, pos6;
	pos4.x = static_cast<float>((rand() % 13) - 6) + 0.5f;
	pos4.y = 1.0f;
	pos4.z = static_cast<float>((rand() % 9) - 4) + 0.5f;

	pos5.x = pos4.x + 2.0f;
	pos5.y = 1.0f;
	pos5.z = pos4.z;
	
	pos6.x = pos4.x + 1.0f;
	pos6.y = 2.5f;
	pos6.z = pos4.z;



	//	pos2.x = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));
	//	pos2.y = 0.5f;
	//	pos2.z = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));
	//	
	//	pos3.x = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));
	//	pos3.y = 0.5f;
	//	pos3.z = -3.5f + static_cast<float>(rand()) / RAND_MAX * (3.5f - (-3.5f));


	_obstacle[0] = new Objects(OBJ_CUBE, pos1, 0.5f, INDEXED);
	_obstacleMat[0] = glm::mat4(1.0f);
	_obstacle[1] = new Objects(OBJ_CUBE, pos2, 0.5f, INDEXED);
	_obstacleMat[1] = glm::mat4(1.0f);
	_obstacle[2] = new Objects(OBJ_CUBE, pos3, 0.5f, INDEXED);
	_obstacleMat[2] = glm::mat4(1.0f);
	
	glm::mat4 move, scale;

	_obstacle[3] = new Objects(OBJ_CUBE, {0.0f, 0.0f, 0.0f}, 0.5f, INDEXED);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(pos4.x - 0.25f, pos4.y, pos4.z));
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 2.0f, 0.5f));
	_obstacleMat[3] = move * scale;
	
	_obstacle[4] = new Objects(OBJ_CUBE, {0.0f, 0.0f, 0.0f}, 0.5f, INDEXED);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(pos5.x + 0.25f, pos5.y, pos5.z));
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 2.0f, 0.5f));
	_obstacleMat[4] = move * scale;

	_obstacle[5] = new Objects(OBJ_CUBE, { 0.0f, 0.0f, 0.0f }, 0.5f, INDEXED);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(pos6.x, pos6.y - 0.25, pos6.z));
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(3.0f, 0.5f, 0.5f));
	_obstacleMat[5] = move * scale;

	// 장애물의 충돌볼륨 미리 만들어놓자

	_oHitbox[0].left = _obstacle[0]->GetCenter().x - _obstacle[0]->GetSize();
	_oHitbox[0].top = _obstacle[0]->GetCenter().y + _obstacle[0]->GetSize();
	_oHitbox[0].right = _obstacle[0]->GetCenter().x + _obstacle[0]->GetSize();
	_oHitbox[0].bottom = _obstacle[0]->GetCenter().y - _obstacle[0]->GetSize();
	_oHitbox[0].front = _obstacle[0]->GetCenter().z + _obstacle[0]->GetSize();
	_oHitbox[0].rear = _obstacle[0]->GetCenter().z - _obstacle[0]->GetSize();
	
	_oHitbox[1].left = _obstacle[0]->GetCenter().x - _obstacle[0]->GetSize();
	_oHitbox[1].top = _obstacle[0]->GetCenter().y + _obstacle[0]->GetSize();
	_oHitbox[1].right = _obstacle[0]->GetCenter().x + _obstacle[0]->GetSize();
	_oHitbox[1].bottom = _obstacle[0]->GetCenter().y - _obstacle[0]->GetSize();
	_oHitbox[1].front = _obstacle[0]->GetCenter().z + _obstacle[0]->GetSize();
	_oHitbox[1].rear = _obstacle[0]->GetCenter().z - _obstacle[0]->GetSize();
	
	_oHitbox[2].left = _obstacle[0]->GetCenter().x - _obstacle[0]->GetSize();
	_oHitbox[2].top = _obstacle[0]->GetCenter().y + _obstacle[0]->GetSize();
	_oHitbox[2].right = _obstacle[0]->GetCenter().x + _obstacle[0]->GetSize();
	_oHitbox[2].bottom = _obstacle[0]->GetCenter().y - _obstacle[0]->GetSize();
	_oHitbox[2].front = _obstacle[0]->GetCenter().z + _obstacle[0]->GetSize();
	_oHitbox[2].rear = _obstacle[0]->GetCenter().z - _obstacle[0]->GetSize();


}

void Ex24::RenderStage()
{

	// GET_SINGLE(TransformManager).Bind(_worldMat * _openLeft * _stageMat[0], _shaderID);
	// _stage[0]->Render();
	// 
	// GET_SINGLE(TransformManager).Bind(_worldMat * _openRight * _stageMat[1], _shaderID);
	// _stage[1]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[2], _shaderID);
	_stage[2]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[3], _shaderID);
	_stage[3]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[4], _shaderID);
	_stage[4]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[5], _shaderID);
	_stage[5]->Render();

	// GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[6], _shaderID);
	// _stage[6]->Render();

	glm::mat4 rot = GET_SINGLE(TransformManager).GetRotateMatrix(180.0f, Z_AXIS);
	for (int i = 0; i < 16; i++)
	{
		float moveX = i - 8 + 0.5;

		for (int j = 0; j < 10; j++)
		{
			float moveZ = j - 5 + 0.5;
			if ((i + j) % 2 == 0)
			{
				glm::mat4 move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(moveX, 0.0f, moveZ));
				_stageMat[6] = move * rot;
				GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[6], _shaderID);
				_stage[6]->Render();
			}
			else
			{
				glm::mat4 move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(moveX, 0.0f, moveZ));
				GET_SINGLE(TransformManager).Bind(_worldMat * _stageMat[7], _shaderID);
				_stage[7]->Render();
			}



		}


	}




}

void Ex24::RenderRobot()
{
	glm::mat4 move = _robotMoveX * _robotMoveY * _robotMoveZ;


	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace * leftLeg, _shaderID);
	_robot[0]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace * rightLeg, _shaderID);
	_robot[1]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace, _shaderID);
	_robot[2]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace * leftArm, _shaderID);
	_robot[3]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace * rightArm, _shaderID);
	_robot[4]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace, _shaderID);
	_robot[5]->Render();

	GET_SINGLE(TransformManager).Bind(_worldMat * move * _robotFace, _shaderID);
	_robot[6]->Render();

}

void Ex24::RenderObstacle()
{

	for (int i = 0; i < 6; i++)
	{
		GET_SINGLE(TransformManager).Bind(_worldMat * _obstacleMat[i], _shaderID);
		_obstacle[i]->Render();
	}



}

void Ex24::OpenStage()
{
	if (_doorAnim)
	{
		glm::mat4 move, rot, mvBack;

		// 1. 왼쪽 문 열기
		move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(4.0f, 0.0f, -4.0f));
		rot = GET_SINGLE(TransformManager).GetRotateMatrix(-_doorDeg, Y_AXIS);
		mvBack = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-4.0f, 0.0f, 4.0f));
		_openLeft = mvBack * rot * move;

		// 2. 오른쪽 문 열기
		move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-4.0f, 0.0f, -4.0f));
		rot = GET_SINGLE(TransformManager).GetRotateMatrix(_doorDeg, Y_AXIS);
		mvBack = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(4.0f, 0.0f, 4.0f));
		_openRight = mvBack * rot * move;

		if (_doorOpen)
		{
			if (_doorDeg <= 120.0f)
				_doorDeg += _doorSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			else
				_doorAnim = false;
		}
		else
		{
			if (_doorDeg >= 0.0f)
				_doorDeg -= _doorSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			else
				_doorAnim = false;
		}

	}

}

void Ex24::RobotJump()
{
	if (isJumped)
	{
		if (jump)
		{
			_yMoveDist += _jumpSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_robotMoveY = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _yMoveDist, 0.0f));
			if (_yMoveDist >= 3.5f)
			{
				jump = false;
			}
		}
		else
		{
			bool isColide = false;
			int colidedIdx = 0;
			for (int i = 0; i < 3; i++)
			{
				if (CheckCollisionBtwHitbox(_rHitbox, _oHitbox[i]))
				{
					isColide = true;
					colidedIdx = i;
					break;
				}
			}

			_yMoveDist -= _jumpSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_robotMoveY = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _yMoveDist, 0.0f));

			if (isColide && _yMoveDist <= _obstacle[colidedIdx]->GetCenter().y + _obstacle[colidedIdx]->GetSize() && _direction != DIR_NONE)	// DIR_NONE이면 올라가기전에 멈춘것 -> 굳이 위에다 올려줄 필요가 없다
			{
				_yMoveDist = _obstacle[colidedIdx]->GetCenter().y + _obstacle[colidedIdx]->GetSize();
				_robotMoveY = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, _yMoveDist, 0.0f));
				return;
			}

			if (_yMoveDist <= 0.0f)
			{
				isJumped = false;
			}
		}
	}
}

void Ex24::RobotWalk()
{
	if (walkPlay)
	{

		switch (_direction)
		{
		case DIR_FRONT:
			_zMoveDist -= _mvSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_robotMoveZ = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, _zMoveDist));
			_robotFace = GET_SINGLE(TransformManager).GetRotateMatrix(180.0f, Y_AXIS);

			if (_zMoveDist <= -4.5f || _zMoveDist >= 4.5f)
				_direction = DIR_BACK;

			break;

		case DIR_BACK:
			_zMoveDist += _mvSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_robotMoveZ = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, _zMoveDist));
			_robotFace = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, Y_AXIS);

			if (_zMoveDist <= -4.5f || _zMoveDist >= 4.5f)
				_direction = DIR_FRONT;

			break;

		case DIR_RIGHT:
			_xMoveDist += _mvSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_robotMoveX = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_xMoveDist, 0.0f, 0.0f));
			_robotFace = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, Y_AXIS);

			if (_xMoveDist <= -7.5f || _xMoveDist >= 7.5f)
				_direction = DIR_LEFT;

			break;

		case DIR_LEFT:
			_xMoveDist -= _mvSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_robotMoveX = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_xMoveDist, 0.0f, 0.0f));
			_robotFace = GET_SINGLE(TransformManager).GetRotateMatrix(-90.0f, Y_AXIS);

			if (_xMoveDist <= -7.5f || _xMoveDist >= 7.5f)
				_direction = DIR_RIGHT;

			break;
		}

		if (CheckCollision())
		{
			_direction = DIR_NONE;
		}
	}
}

void Ex24::RobotWalkAnim()
{
	if (walkPlay && _direction != DIR_NONE)
	{
		glm::mat4 tMat, mvMat, rotMat, mvBackMat;

		// 1. 왼다리
		mvMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-(_robot[0]->GetCenter().x), -0.5f, -(_robot[0]->GetCenter().z)));
		rotMat = GET_SINGLE(TransformManager).GetRotateMatrix(walkDeg, X_AXIS);
		mvBackMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3((_robot[0]->GetCenter().x), 0.5f, (_robot[0]->GetCenter().z)));
		leftLeg = mvBackMat * rotMat * mvMat;

		// 2. 오른다리
		mvMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-(_robot[1]->GetCenter().x), -0.5f, -(_robot[1]->GetCenter().z)));
		rotMat = GET_SINGLE(TransformManager).GetRotateMatrix(-walkDeg, X_AXIS);
		mvBackMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3((_robot[1]->GetCenter().x), 0.5f, (_robot[1]->GetCenter().z)));
		rightLeg = mvBackMat * rotMat * mvMat;

		// 1. 왼팔
		mvMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-(_robot[3]->GetCenter().x), -1.3f, -(_robot[3]->GetCenter().z)));
		rotMat = GET_SINGLE(TransformManager).GetRotateMatrix(walkDeg, X_AXIS);
		mvBackMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3((_robot[3]->GetCenter().x), 1.3f, (_robot[3]->GetCenter().z)));
		leftArm = mvBackMat * rotMat * mvMat;

		// 2. 오른팔
		mvMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-(_robot[4]->GetCenter().x), -1.3f, -(_robot[4]->GetCenter().z)));
		rotMat = GET_SINGLE(TransformManager).GetRotateMatrix(-walkDeg, X_AXIS);
		mvBackMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3((_robot[4]->GetCenter().x), 1.3f, (_robot[4]->GetCenter().z)));
		rightArm = mvBackMat * rotMat * mvMat;

		walk += swingSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
		walkDeg = glm::sin(glm::radians(walk)) * _maxWalkDeg;
	}
	else
	{
		leftLeg = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
		rightLeg = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
		leftArm = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
		rightArm = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
		walk = 0.0f;
		walkDeg = 0.0f;
	}

}

void Ex24::PlayCameraAnim()
{
	if (_camRotatePlay)
	{
		if (_camRotateDir)
		{
			_camRotateDeg += _camRotateSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_camera->CameraRevolution(_camRotateDeg, Y_AXIS);
		}
		else
		{
			_camRotateDeg -= _camRotateSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_camera->CameraRevolution(_camRotateDeg, Y_AXIS);
		}
	}

}

bool Ex24::CheckCollision()
{
	_rHitbox = GetRobotHitboxXZ();	// 갱신

	for (int i = 0; i < 3; i++)
	{
		if (!CheckCollisionBtwHitbox(_rHitbox, _oHitbox[i]))
			continue;
		if (_yMoveDist >= _obstacle[i]->GetCenter().y + _obstacle[i]->GetSize())	// 점프해서 높이가 장애물보다 높으면 충돌아님
			continue;

		return true;
	}

	return false;

	//	이전 Objects의 GetCollosion, 여기의 HITBOX는 각 점의 좌표값
	//	if (h1.p2.x > h2.p1.x && h2.p2.x > h1.p1.x && h1.p1.y > h2.p4.y && h2.p1.y > h1.p4.y)
	//		return true;
	//	else
	//		return false;

}

bool Ex24::CheckCollisionBtwHitbox(HITBOX h1, HITBOX h2)
{
	if (h1.right > h2.left && h2.right > h1.left && h1.top > h2.bottom && h2.top > h1.bottom && h1.front > h2.rear && h2.front > h1.rear)
	{
		return true;
	}
	else
		return false;
}

HITBOX Ex24::GetRobotHitboxXZ()
{
	switch (_direction)
	{
	case DIR_FRONT:
	case DIR_BACK:
		_rHitbox = { _xMoveDist - 0.5f, _yMoveDist + 1.7f, _zMoveDist + 0.1f, _yMoveDist, _xMoveDist + 0.5f, _zMoveDist - 0.1f };
		break;

	case DIR_LEFT:
	case DIR_RIGHT:
		_rHitbox = { _xMoveDist - 0.1f,_yMoveDist + 1.7f, _zMoveDist + 0.5f, _yMoveDist, _xMoveDist + 0.1f, _zMoveDist - 0.5f };
		break;
	}

	return _rHitbox;
}
