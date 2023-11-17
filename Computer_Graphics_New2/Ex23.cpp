#include "pch.h"
#include "Ex23.h"

Ex23::Ex23()
{
	InitEx();
}

Ex23::~Ex23()
{
}

void Ex23::InitEx()
{
	srand(time(0));
	_camera = new Camera(glm::vec3(0.0, 0.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
}

void Ex23::drawScene()
{	
	_deltaTime = GET_SINGLE(TimeManager).GetDeltaTime();
	_shaderID = GET_SINGLE(Core).GetuShaderID();
	glUseProgram(_shaderID);

	_camera->Bind(_shaderID);
	_projection->Bind(_shaderID);
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);

	if (_cubeState == CS_MOVING && _cubeList.size() <= 0)
	{
		MakeCube();
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	KeyboardUpdate();
	MouseUpdate();
	MotionUpdate();

	RotateScreenAnim();
	CubeMove();
	BallMoveAnim();
	OpenDoorAnim();

	CheckCollision();

	DrawAxis(3.0f);
	Render();

	glutSwapBuffers();


}

void Ex23::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex23::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();
	if (ks == nullptr)
	{
		return;
	}

	switch (ks->key)
	{
	case 'y':
		if (!_rotPlay)
			_rotPlay = true;
		else if (_rotPlay && _rotDir)
			_rotPlay = false;

		_rotDir = true;

		break;

	case 'Y':
		if (!_rotPlay)
			_rotPlay = true;
		else if (_rotPlay && !_rotDir)
			_rotPlay = false;

		_rotDir = false;

		break;

	case 'z':
		_camera->CameraMove(glm::vec3(0.0f, 0.0f, 1.0f));
		break;
		
	case 'Z':
		_camera->CameraMove(glm::vec3(0.0f, 0.0f, -1.0f));
		break;

	case 'o':
		if (!_openDoorPlay)
			_openDoorPlay = true;
		else if (_openDoorPlay && _rotDir)
			_openDoorPlay = false;

		_doorOpen = true;
		break;

	case 'O':
		if (!_openDoorPlay)
			_openDoorPlay = true;
		else if (_openDoorPlay && _rotDir)
			_openDoorPlay = false;

		_doorOpen = false;
		break;


	case 'b':
		MakeBall();
		break;

	}

	delete ks;
}

void Ex23::MouseUpdate()
{
	MouseState* ms = GET_SINGLE(InputManager).DequeueMouseBuf();
	if (ms == nullptr)
	{
		return;
	}

	if(ms->button == GLUT_LEFT && ms->state == GLUT_DOWN)
		_mousePrevPos = { ms->pos.x, ms->pos.y, 0.0f };

	delete ms;
}

void Ex23::MotionUpdate()
{
	Coord* ms = GET_SINGLE(InputManager).DequeueMotionBuf();
	if (ms == nullptr)
	{
		return;
	}

	float dx = ms->x - _mousePrevPos.x;
	_mousePrevPos = { ms->x, ms->y, 0.0f };

	RotateCube(dx);

	delete ms;
}

void Ex23::RotateScreenAnim()
{
	if (!_rotPlay)
		return;

	if (_rotDir)
	{
		_rotation += 40.0f * _deltaTime;
		_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(_rotation, Y_AXIS);
	}
	else
	{
		_rotation -= 40.0f * _deltaTime;
		_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(_rotation, Y_AXIS);
	}


}

void Ex23::BallMoveAnim()
{

	for (int i = _ballList.size() - 1; i >= 0; i--)
	{
		if(_ballState == BS_BOUNCE)
		{
			_ballList.at(i).posVector += _ballList.at(i).dirVector * _ballSpeed * GET_SINGLE(TimeManager).GetDeltaTime();

			// 무대가 돌아가있음도 고려
			glm::mat4 rot = GET_SINGLE(TransformManager).GetRotateMatrix(_planeRotDeg, Z_AXIS);
			_ballList.at(i).ballMat = rot * GET_SINGLE(TransformManager).GetTranslateMatrix(_ballList.at(i).posVector);
		}
		else if(_ballState == BS_FALLING)
		{
			_ballList.at(i).posVector += _gravityVector * _ballList.at(i).ballFallingSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_ballList.at(i).ballFallingSpeed += _gravity * GET_SINGLE(TimeManager).GetDeltaTime();

			// 무대가 돌아가있음도 고려
			glm::mat4 rot = GET_SINGLE(TransformManager).GetRotateMatrix(_planeRotDeg, Z_AXIS);
			_ballList.at(i).ballMat = rot * GET_SINGLE(TransformManager).GetTranslateMatrix(_ballList.at(i).posVector);
		}


		if (_ballList.at(i).posVector[0] >= 10.0f || _ballList.at(i).posVector[0] <= -10.0f
			|| _ballList.at(i).posVector[1] >= 10.0f || _ballList.at(i).posVector[1] <= -10.0f
			|| _ballList.at(i).posVector[2] >= 10.0f || _ballList.at(i).posVector[2] <= -10.0f)
		{
			_ballList.erase(_ballList.begin() + i);
			_ballList.shrink_to_fit();
		}
	}


}

void Ex23::OpenDoorAnim()
{
	// 바닥 문은 벡터 5,6 인덱스에 저장됨. 각각 왼쪽, 오른쪽
	if (_planeList.size() == 0)
		return;

	if (_openDoorPlay) 
	{
		glm::mat4 invLeft = glm::inverse(_planeList.at(5).moveMat);
		glm::mat4 invRight = glm::inverse(_planeList.at(6).moveMat);

		glm::mat4 addMoveLeft = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-2.0f, 0.0f, 0.0f));
		glm::mat4 addMoveRight = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(2.0f, 0.0f, 0.0f));

		glm::mat4 leftMat = GET_SINGLE(TransformManager).GetRotateMatrix(-_openDegree, Z_AXIS);
		glm::mat4 RightMat = GET_SINGLE(TransformManager).GetRotateMatrix(_openDegree, Z_AXIS);

		_openLeft = addMoveLeft * _planeList.at(5).moveMat * leftMat * invLeft * glm::inverse(addMoveLeft);
		_openRight = addMoveRight * _planeList.at(6).moveMat * RightMat * invRight * glm::inverse(addMoveRight);
		
		if (_doorOpen)
		{
			if (_ballState == BS_BOUNCE)
			{
				_ballState = BS_FALLING;
			}

			if (_cubeState == CS_MOVING)
			{
				_cubeState = CS_FALLING;
			}


			if (_openDegree <= 120.0f)
			{
				_openDegree += _openSpeed * _deltaTime;
			}
			else
			{
				_openDoorPlay = false;
			}
		}
		else
		{
			if (_openDegree > 0.0f)
			{
				_openDegree -= _openSpeed * _deltaTime;
			}
			else
			{

				glm::mat4 leftMat = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, Z_AXIS);
				glm::mat4 RightMat = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, Z_AXIS);

				_ballState = BS_BOUNCE;
				_cubeState = CS_MOVING;
				_openDoorPlay = false;
			}
		}
	}

}

void Ex23::RotateCube(float dx)
{
	if (_planeRotDeg > 60)
	{
		_planeRotDeg = 60;
		return;
	}
	if (_planeRotDeg < -60)
	{
		_planeRotDeg = -60;
		return;
	}
		

	_planeRotDeg += dx * 30;
	_planeRotMat = GET_SINGLE(TransformManager).GetRotateMatrix(_planeRotDeg, Z_AXIS);
	
	// 법선벡터와 평면위의 점도 회전시켜주어야함
	//	for (int i = 0; i < _planeList.size(); i++)
	//	{
	//		NormalUpdate(static_cast<PlaneIndex>(i), _planeRotMat);
	//	}

	


}

void Ex23::CubeMove()
{
	glm::vec3 moveVec = glm::vec3(1.0f);
	float deltaT = GET_SINGLE(TimeManager).GetDeltaTime();
	for (int i = 0; i < _cubeList.size(); i++)
	{
		if (_cubeState == CS_MOVING)
		{
			if (_planeRotDeg == 0.0f)
				break;

			if (_planeRotDeg > 0.0f)
			{
				moveVec = glm::vec3(-1.0f, 0.0f, 0.0f);
			}
			else if (_planeRotDeg < 0.0f)
			{
				moveVec = glm::vec3(1.0f, 0.0f, 0.0f);
			}

			if (prevDir[0] != moveVec[0])
			{
				_cubeList.at(i).cubeMovingSpeed = 0.0f;
			}


			// 2. 무대가 돌아가있음도 고려
			glm::mat4 rot = GET_SINGLE(TransformManager).GetRotateMatrix(_planeRotDeg, Z_AXIS);


			_cubeList.at(i).posVector += moveVec * glm::abs(_cubeList.at(i).cubeMovingSpeed) * deltaT;
			CubeAABBUpdate();

			if (isIntersectBtwCube(_cubeList.at(i).cubeAABB))
			{
				_cubeList.at(i).posVector -= moveVec * glm::abs(_cubeList.at(i).cubeMovingSpeed) * deltaT;
				_cubeList.at(i).cubeMovingSpeed = 0.0f;
			}

			_cubeList.at(i).cubeMat = rot * GET_SINGLE(TransformManager).GetTranslateMatrix(_cubeList.at(i).posVector);


			// 3. 기울어진 방향대로 내려갈 가속도: 중력가속도 * sin
			float slopeAcc = _gravity * 0.1f * _cubeList.at(i).cubeWeight;
			_cubeList.at(i).cubeMovingSpeed += slopeAcc * GET_SINGLE(TimeManager).GetDeltaTime();
		}
		else if (_cubeState == CS_FALLING)
		{
			_cubeList.at(i).posVector += _gravityVector * _cubeList.at(i).cubeFallingSpeed * GET_SINGLE(TimeManager).GetDeltaTime();
			_cubeList.at(i).cubeFallingSpeed += _gravity * GET_SINGLE(TimeManager).GetDeltaTime();

			// 무대가 돌아가있음도 고려
			glm::mat4 rot = GET_SINGLE(TransformManager).GetRotateMatrix(_planeRotDeg, Z_AXIS);
			_cubeList.at(i).cubeMat = rot * GET_SINGLE(TransformManager).GetTranslateMatrix(_cubeList.at(i).posVector);
		}

		if (_cubeList.at(i).posVector[0] >= 10.0f || _cubeList.at(i).posVector[0] <= -10.0f
			|| _cubeList.at(i).posVector[1] >= 10.0f || _cubeList.at(i).posVector[1] <= -10.0f
			|| _cubeList.at(i).posVector[2] >= 10.0f || _cubeList.at(i).posVector[2] <= -10.0f)
		{
			_cubeList.erase(_cubeList.begin() + i);
			_cubeList.shrink_to_fit();
		}
	}
	prevDir = moveVec;

}

void Ex23::Render()
{
	if (_planeList.size() == 0)
	{
		MakeStage();
		MakeCube();
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	RenderStage();
	RenderBall();
	RenderCube();
}

void Ex23::MakeStage()
{
	glm::mat4 scale, rot, move;

	// 오른쪽
	planeInfo temp1;
	temp1.planeObj = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(-90.0f, Z_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(4.0f, 0.0f, 0.0f));
	temp1.moveMat = move;
	temp1.planeMat = move * rot;
	temp1.planeColor = { 0.2f,0.2f,0.2f };
	temp1.planeNormalOrigin = { -1.0f, 0.0f, 0.0f };
	temp1.pointOnPlaneOrigin = { 4.0, 0.0, 0.0 };
	temp1.planeNormal = temp1.planeNormalOrigin;
	temp1.pointOnPlane = temp1.pointOnPlaneOrigin;
	_planeList.push_back(temp1);

	// 왼쪽
	planeInfo temp2;
	temp2 .planeObj = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, Z_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-4.0f, 0.0f, 0.0f));
	temp2.moveMat = move;
	temp2.planeMat = move * rot;
	temp2.planeColor = { 0.2f,0.2f,0.2f };
	temp2.planeNormalOrigin = { 1.0f, 0.0f, 0.0f };
	temp2.pointOnPlaneOrigin = { -4.0, 4.0, 0.0 };
	temp2.planeNormal = temp2.planeNormalOrigin;
	temp2.pointOnPlane = temp2.pointOnPlaneOrigin;
	_planeList.push_back(temp2);


	// 위
	planeInfo temp3;
	temp3.planeObj = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	temp3.planeMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 4.0f, 0.0f));
	temp3.moveMat = temp3.planeMat;
	temp3.planeColor = { 0.5f,0.5f,0.5f };
	temp3.planeNormalOrigin = { 0.0f, -1.0f, 0.0f };
	temp3.pointOnPlaneOrigin = { 0.0f, 4.0f, 0.0f };
	temp3.planeNormal = temp3.planeNormalOrigin;
	temp3.pointOnPlane = temp3.pointOnPlaneOrigin;
	_planeList.push_back(temp3);

	// 앞
	planeInfo temp4;
	temp4.planeObj = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(90.0f, X_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 4.0f));
	temp4.moveMat = move;
	temp4.planeMat = move * rot;
	temp4.planeColor = { 0.7f, 0.7f, 0.7f };
	temp4.planeNormalOrigin = { 0.0f, 0.0f, -1.0f };
	temp4.pointOnPlaneOrigin = { 0.0f, 0.0f, 4.0f };
	temp4.planeNormal = temp4.planeNormalOrigin;
	temp4.pointOnPlane = temp4.pointOnPlaneOrigin;
	_planeList.push_back(temp4);

	// 뒤
	planeInfo temp5;
	temp5.planeObj = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(-90.0f, X_AXIS);
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -4.0f));
	temp5.moveMat = move;
	temp5.planeMat = move * rot;
	temp5.planeColor = { 0.7f,0.7f,0.7f };
	temp5.planeNormalOrigin = { 0.0f, 0.0f, 1.0f };
	temp5.pointOnPlaneOrigin = { 0.0f, 0.0f, -4.0f };
	temp5.planeNormal = temp5.planeNormalOrigin;
	temp5.pointOnPlane = temp5.pointOnPlaneOrigin;
	_planeList.push_back(temp5);

	// 바닥 왼쪽
	planeInfo temp6;
	temp6.planeObj = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(180.0f, Z_AXIS);
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 1.0f, 1.0f));
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-2.0f, -4.0f, 0.0f));
	temp6.moveMat = move;
	temp6.planeMat = move * scale * rot;
	temp6.planeColor = { 0.5f,0.5f,0.5f };
	temp6.planeNormalOrigin = { 0.0f, 1.0f, 0.0f };
	temp6.pointOnPlaneOrigin = { 0.0f, -4.0f, 0.0f };
	temp6.planeNormal = temp6.planeNormalOrigin;
	temp6.pointOnPlane = temp6.pointOnPlaneOrigin;
	_planeList.push_back(temp6);
	
	// 바닥 오른쪽
	planeInfo temp7;
	temp7.planeObj = new Objects(OBJ_PLANE_RECT, { 0,0,0 }, 4.0f, INDEXED);
	rot = GET_SINGLE(TransformManager).GetRotateMatrix(180.0f, Z_AXIS);
	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 1.0f, 1.0f));
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(2.0f, -4.0f, 0.0f));
	temp7.moveMat = move;
	temp7.planeMat = move * scale * rot;
	temp7.planeColor = { 0.5f,0.5f,0.5f };
	temp7.planeNormalOrigin = { 0.0f, 1.0f, 0.0f };
	temp7.pointOnPlaneOrigin = { 0.0f, -4.0f, 0.0f };
	temp7.planeNormal = temp7.planeNormalOrigin;
	temp7.pointOnPlane = temp7.pointOnPlaneOrigin;
	_planeList.push_back(temp7);
}

void Ex23::MakeBall()
{
	if (_ballList.size() >= 5)
	{
		return;
	}

	BallInfo temp;
	temp.ballObj = new Objects(QOBJ_SPHERE, { 0.0f,0.0f,0.0f }, _ballRadius, GLU_FILL, _ballColor);
	
	temp.dirVector[0] = static_cast<float>(rand()) / (RAND_MAX / 2) - 1.0f;
	temp.dirVector[1] = static_cast<float>(rand()) / (RAND_MAX / 2) - 1.0f;
	temp.dirVector[2] = static_cast<float>(rand()) / (RAND_MAX / 2) - 1.0f;
	
	temp.dirVector = glm::normalize(temp.dirVector);

	_ballList.push_back(temp);
	
}

void Ex23::MakeCube()
{
	CubeInfo temp1;
	temp1.cubeSize = 0.7f;
	temp1.cubeObj = new Objects(temp1.cubeSize, temp1.cubeSize, -temp1.cubeSize, -temp1.cubeSize, 0.0, temp1.cubeSize * 2);
	temp1.posVector = { 0.0f, -4.0f, -2.0f };
	temp1.cubeMat = GET_SINGLE(TransformManager).GetTranslateMatrix(temp1.posVector);
	temp1.cubeWeight = 3.0f;
	_cubeList.push_back(temp1);

	CubeInfo temp2;
	temp2.cubeSize = 0.5f;
	temp2.cubeObj = new Objects(temp2.cubeSize, temp2.cubeSize, -temp2.cubeSize, -temp2.cubeSize, 0.0, temp2.cubeSize * 2);
	temp2.posVector = { 0.0f, -4.0f, 0.0f };
	temp2.cubeMat = GET_SINGLE(TransformManager).GetTranslateMatrix(temp2.posVector);
	temp2.cubeWeight = 2.0f;
	_cubeList.push_back(temp2);

	CubeInfo temp3;
	temp3.cubeSize = 0.3f;
	temp3.cubeObj = new Objects(temp3.cubeSize, temp3.cubeSize, -temp3.cubeSize, -temp3.cubeSize, 0.0, temp3.cubeSize * 2);
	temp3.posVector = { 0.0f, -4.0f, 2.0f };
	temp3.cubeMat = GET_SINGLE(TransformManager).GetTranslateMatrix(temp3.posVector);
	temp3.cubeWeight = 1.0f;
	_cubeList.push_back(temp3);

	CubeAABBUpdate();
}

void Ex23::RenderStage()
{
	unsigned int uniformLoc = glGetUniformLocation(GET_SINGLE(Core).GetuShaderID(), "uniformColor");

	for (int i = 0; i < _planeList.size(); i++)
	{
		glUniform3f(uniformLoc, _planeList.at(i).planeColor.Red, _planeList.at(i).planeColor.Green, _planeList.at(i).planeColor.Blue);

		if (i == 5)
			GET_SINGLE(TransformManager).Bind(_worldMat * _planeRotMat * _openLeft * _planeList.at(i).planeMat, _shaderID);
		else if (i == 6)
			GET_SINGLE(TransformManager).Bind(_worldMat * _planeRotMat * _openRight * _planeList.at(i).planeMat, _shaderID);
		else
			GET_SINGLE(TransformManager).Bind(_worldMat * _planeRotMat * _planeList.at(i).planeMat, _shaderID);
		

		_planeList.at(i).planeObj->Render();
	}

}

void Ex23::RenderBall()
{
	unsigned int uniformLoc = glGetUniformLocation(GET_SINGLE(Core).GetuShaderID(), "uniformColor");

	for (int i = 0; i < _ballList.size(); i++)
	{
		glUniform3f(uniformLoc, _ballColor.Red, _ballColor.Green, _ballColor.Blue);

		GET_SINGLE(TransformManager).Bind(_worldMat * _ballList.at(i).ballMat, _shaderID);
		_ballList.at(i).ballObj->Render();

	}


}

void Ex23::RenderCube()
{
	unsigned int uniformLoc = glGetUniformLocation(GET_SINGLE(Core).GetuShaderID(), "uniformColor");

	for (int i = 0; i < _cubeList.size(); i++)
	{
		glUniform3f(uniformLoc, _cubeColor.Red, _cubeColor.Green, _cubeColor.Blue);

		GET_SINGLE(TransformManager).Bind(_worldMat * _cubeList.at(i).cubeMat, _shaderID);
		_cubeList.at(i).cubeObj->Render();
	}
}

void Ex23::CheckCollision()
{
	for (int i = 0; i < _ballList.size(); i++)
	{
		for (int j = 0; j < _planeList.size()-1; j++)
		{
			if (isIntersect(_ballList.at(i).posVector, _ballRadius, _planeList.at(j).planeNormalOrigin, _planeList.at(j).pointOnPlaneOrigin))
			{
				_ballList.at(i).dirVector = glm::reflect(_ballList.at(i).dirVector, _planeList.at(j).planeNormal);
			}
		}
	}
}

bool Ex23::isIntersect(glm::vec3& center, float radius, glm::vec3& normal, glm::vec3& pointOnPlane)
{
	// 구의 중심을 평면에 수직으로 투영
	glm::vec3 projectedPoint = center - glm::dot(center - pointOnPlane, normal) * normal;

	// 평면 위의 한 점과 투영된 점 간의 거리 계산
	float distance = glm::length(projectedPoint - center);

	// 거리와 구의 반지름 비교
	return distance <= radius;
}


bool Ex23::isIntersectBtwCube(AABB bound)
{
	AABB curr = bound;
	if (curr.left <= -4.0f || curr.right >= 4.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Ex23::CubeAABBUpdate()
{
	for (int i = 0; i < _cubeList.size(); i++)
	{
		_cubeList.at(i).cubeAABB.left = _cubeList.at(i).posVector[0] - _cubeList.at(i).cubeSize;
		_cubeList.at(i).cubeAABB.top = _cubeList.at(i).posVector[1] + _cubeList.at(i).cubeSize;
		_cubeList.at(i).cubeAABB.right = _cubeList.at(i).posVector[0] + _cubeList.at(i).cubeSize;
		_cubeList.at(i).cubeAABB.bottom = _cubeList.at(i).posVector[1] - _cubeList.at(i).cubeSize;
	}

}

void Ex23::NormalUpdate(PlaneIndex index, glm::mat4 Matrix)
{
	int idx = static_cast<int>(index);

	glm::vec4 normalTemp = glm::vec4(_planeList.at(idx).planeNormalOrigin, 1.0f);
	glm::vec4 pointTemp = glm::vec4(_planeList.at(idx).pointOnPlaneOrigin, 0.0f);

	normalTemp = Matrix * normalTemp;
	pointTemp = Matrix * pointTemp;

	_planeList.at(idx).planeNormal = { normalTemp[0], normalTemp[1], normalTemp[2] };
	_planeList.at(idx).pointOnPlane = { pointTemp[0], pointTemp[1], pointTemp[2] };
}
