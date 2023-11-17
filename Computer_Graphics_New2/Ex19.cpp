#include "pch.h"
#include "Ex19.h"

Ex19::Ex19()
{
	InitEx();
}

Ex19::~Ex19()
{
}

void Ex19::InitEx()
{
	cout << "p / P: 직각 투영 / 원근 투영" << endl;
	cout << "m / M : 솔리드 모델 / 와이어 모델" << endl;
	cout << "w / a / s / d : 위의 도형들을 좌 / 우 / 상 / 하로 이동(x축과 y축 값 이동 - 객체 이동)" << endl;
	cout << "+ / -: 위의 도형들을 앞 / 뒤로 이동(z축 값 이동 - 객체 이동)" << endl;
	cout << "y / Y : 전체 객체들을 y축으로 양 / 음 방향으로 회전(중앙의 구의 y축에 대하여 회전)" << endl;
	cout << "z / Z : 중심의 구를 제외하고 행성, 달, 궤도가 z축에 대하여 양 / 음 방향으로 일제히 회전" << endl;




	_worldMat = GET_SINGLE(TransformManager).GetRotateMatrix(20.0f, X_AXIS);

	_orbit1 = glm::mat4(1.0f);
	_orbit2 = GET_SINGLE(TransformManager).GetRotateMatrix(45.0f, Z_AXIS);
	_orbit3 = GET_SINGLE(TransformManager).GetRotateMatrix(-45.0f, Z_AXIS);

	_parentMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(3.0f, 0.0f, 0.0f));
	_parentMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -3.0f));
	_parentMat3 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 3.0f));
	
	_childMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(4.0f, 0.0f, 0.0f));
	_childMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -4.0f));
	_childMat3 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 4.0f));
	
	_lastMat1 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(1.0f, 0.0f, 0.0f));
	_lastMat2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -1.0f));
	_lastMat3 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 1.0f));

	_scaleMat1 = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.4f, 0.4f, 0.4f));
	_scaleMat2 = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.2f, 0.2f, 0.2f));

	_yAnimMat = GET_SINGLE(TransformManager).GetRotateMatrix(_yAnimDeg, Y_AXIS);
	_zAnimMat = GET_SINGLE(TransformManager).GetRotateMatrix(_zAnimDeg, Z_AXIS);

	_camera = new Camera(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -8.0f);

	
}

void Ex19::drawScene()
{
	shaderID = GET_SINGLE(Core).GetuShaderID();
	glUseProgram(shaderID);
	colorLocation = glGetUniformLocation(GET_SINGLE(Core).GetuShaderID(), "uniformColor");
	KeyboardUpdate();
	_camera->Bind(GET_SINGLE(Core).GetuShaderID());
	if (_perspective)
	{
		_projection->SetPerspectiveProjection(45.0f, 1.0f, 0.1f, 50.0f, -7.0f);
		_projection->Bind(GET_SINGLE(Core).GetuShaderID());
	}
	else
	{
		_projection->SetOrthoProjection(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
		_projection->Bind(GET_SINGLE(Core).GetuShaderID());
	}
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _yAnimMat * _zAnimMat, shaderID);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PlayAnim();
	Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Ex19::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex19::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();
	if (ks == nullptr)
		return;

	switch (ks->key)
	{
	case 'p':
		_perspective = false;
		break;

	case 'P':
		_perspective = true;
		break;

	case 'm':
		_planet->SetQuadricDrawType(GLU_FILL);
		break;

	case 'M':
		_planet->SetQuadricDrawType(GLU_LINE);
		break;

	case 'w':
		MoveSystem(DIR_UP);
		break;
		
	case 's':
		MoveSystem(DIR_DOWN);
		break;
		
	case 'a':
		MoveSystem(DIR_LEFT);
		break;
		
	case 'd':
		MoveSystem(DIR_RIGHT);
		break;
		
	case '+':
		MoveSystem(DIR_FRONT);
		break;
		
	case '-':
		MoveSystem(DIR_BACK);
		break;

	case 'y':
		if(!_yRotateAnim)
			_yRotateAnim = true;
		else
			_yRotateAnim = false;

		_yRotateDirection = true;

		break;
		
	case 'Y':
		if (!_yRotateAnim)
			_yRotateAnim = true;
		else
			_yRotateAnim = false;

		_yRotateDirection = false;

		break;
		
	case 'z':
		if (!_zRotateAnim)
			_zRotateAnim = true;
		else
			_zRotateAnim = false;

		_zRotateDirection = true;

		break;
		
	case 'Z':
		if (!_zRotateAnim)
			_zRotateAnim = true;
		else
			_zRotateAnim = false;

		_zRotateDirection = false;

		break;

	}


	delete ks;
}

void Ex19::Render()
{
	if (_bigOrbit == nullptr)
	{
		SetOrbit();
		SetPlanet();
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	RenderOrbit();
	RenderPlanet();
	
	yRot1 = GET_SINGLE(TransformManager).GetRotateMatrix(yDeg1, Y_AXIS);
	yDeg1 += 0.05f;
	
	yRot2 = GET_SINGLE(TransformManager).GetRotateMatrix(yDeg2, Y_AXIS);
	yDeg2 += 0.03f;
	
	yRot3 = GET_SINGLE(TransformManager).GetRotateMatrix(yDeg3, Y_AXIS);
	yDeg3 += 0.15f;

}

void Ex19::SetOrbit()
{
	float degree = 0.0f;
	int idx = 0;
	while (degree <= 360.0f)
	{
		Coord pos = { 0.0f, 0.0f, 0.0f };
		pos.x = _bigOrbitRadius * glm::cos(glm::radians(degree));
		pos.z = _bigOrbitRadius * glm::sin(glm::radians(degree));
		
		_bigOrbitVBuf[idx] = pos.x;
		_bigOrbitVBuf[idx + 1] = pos.y;
		_bigOrbitVBuf[idx + 2] = pos.z;

		_bigOrbitCBuf[idx] = 0.0f;
		_bigOrbitCBuf[idx + 1] = 0.0f;
		_bigOrbitCBuf[idx + 2] = 0.0f;

		degree += 10.0f;
		idx += 3;
	}

	_bigOrbit = new VAO(_bigOrbitVBuf, _bigOrbitCBuf, idx);

	degree = 0.0f;
	idx = 0;
	while (degree <= 360.0f)
	{
		Coord pos = { 0.0f, 0.0f, 0.0f };
		pos.x = _smallOrbitRadius * glm::cos(glm::radians(degree));
		pos.z = _smallOrbitRadius * glm::sin(glm::radians(degree));

		_smallOrbitVBuf[idx] = pos.x;
		_smallOrbitVBuf[idx + 1] = pos.y;
		_smallOrbitVBuf[idx + 2] = pos.z;

		_smallOrbitCBuf[idx] = 0.0f;
		_smallOrbitCBuf[idx + 1] = 0.0f;
		_smallOrbitCBuf[idx + 2] = 0.0f;

		degree += 10.0f;
		idx += 3;
	}

	_smallOrbit = new VAO(_smallOrbitVBuf, _smallOrbitCBuf, idx);
}

void Ex19::SetPlanet()
{
	// 1. 조상: 중심점, 부모행성 3개를 자식으로 가짐
	_planet = new Objects(QOBJ_SPHERE, {0.0f, 0.0f, 0.0f}, 1.0f, GLU_LINE, {0.0f, 0.0f, 1.0f});

}

void Ex19::RenderOrbit()
{
	glUseProgram(GET_SINGLE(Core).GetuShaderID());
	unsigned int uniformLoc = glGetUniformLocation(GET_SINGLE(Core).GetuShaderID(), "uniformColor");

	glBindVertexArray(_bigOrbit->GetVAOHandle());
	int bufSize = _bigOrbit->GetVertexCount();

	float color[] = { 0.0f, 0.0f, 0.0f };
	glUniform3f(uniformLoc, color[0], color[1], color[2]);

	GET_SINGLE(TransformManager).Bind(_worldMat * _yAnimMat * _zAnimMat * _orbit1, shaderID);
	for (int i = 0; i < (bufSize / 3) - 1; i++)													
	{																							
		glDrawArrays(GL_LINES, i, 2);															
	}																							
																								
	GET_SINGLE(TransformManager).Bind(_worldMat * _yAnimMat * _zAnimMat * _orbit2, shaderID);
	for (int i = 0; i < (bufSize / 3) - 1; i++)													
	{																							
		glDrawArrays(GL_LINES, i, 2);															
	}																							
																								
	GET_SINGLE(TransformManager).Bind(_worldMat * _yAnimMat * _zAnimMat * _orbit3, shaderID);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}
	
	glBindVertexArray(_smallOrbit->GetVAOHandle());
	bufSize = _smallOrbit->GetVertexCount();

	GET_SINGLE(TransformManager).Bind(_worldMat * _yAnimMat * _zAnimMat * yRot2 * _parentMat1, shaderID);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _yAnimMat * _zAnimMat * (_orbit2 * yRot2) * _parentMat2, shaderID);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}
	
	GET_SINGLE(TransformManager).Bind(_worldMat * _yAnimMat * _zAnimMat * (_orbit3 * yRot2) * _parentMat3, shaderID);
	for (int i = 0; i < (bufSize / 3) - 1; i++)
	{
		glDrawArrays(GL_LINES, i, 2);
	}

}

void Ex19::RenderPlanet()
{
	glUseProgram(GET_SINGLE(Core).GetuShaderID());
	unsigned int uniformLoc = glGetUniformLocation(GET_SINGLE(Core).GetuShaderID(), "uniformColor");

	float color[] = { 0.0f, 0.0f, 1.0f };
	glUniform3f(uniformLoc, color[0], color[1], color[2]);

	glm::mat4 currMat = _worldMat * _yAnimMat * _ancestorMat * yRot1;
	GET_SINGLE(TransformManager).Bind(currMat, shaderID);
	_planet->Render();
	
	
	// 부모;
	color[0] = 0.0f;
	color[1] = 1.0f;
	color[2] = 0.0f;
	glUniform3f(uniformLoc, color[0], color[1], color[2]);

	currMat = _worldMat * _yAnimMat * _zAnimMat * (_orbit1 * yRot2) * (_parentMat1 * yRot1) * _scaleMat1;
	GET_SINGLE(TransformManager).Bind(currMat, shaderID);
	_planet->Render();

	currMat = _worldMat * _yAnimMat * _zAnimMat * (_orbit2 * yRot2) * (_parentMat2 * yRot1) * _scaleMat1;
	GET_SINGLE(TransformManager).Bind(currMat, shaderID);
	_planet->Render();

	currMat = _worldMat * _yAnimMat * _zAnimMat * (_orbit3 * yRot2) * (_parentMat3 * yRot1) * _scaleMat1;
	GET_SINGLE(TransformManager).Bind(currMat, shaderID);
	_planet->Render();
	
	
	// 자식
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	glUniform3f(uniformLoc, color[0], color[1], color[2]);

	currMat = _worldMat * _yAnimMat * _zAnimMat * (_orbit1 * yRot2) * _parentMat1 * (yRot3) * (_lastMat1 * yRot1) * _scaleMat2;
	GET_SINGLE(TransformManager).Bind(currMat, shaderID);
	_planet->Render();

	currMat = _worldMat * _yAnimMat * _zAnimMat * (_orbit2 * yRot2) * _parentMat2 * (yRot3) * (_lastMat2 * yRot1) * _scaleMat2;
	GET_SINGLE(TransformManager).Bind(currMat, shaderID);
	_planet->Render();

	currMat = _worldMat * _yAnimMat * _zAnimMat * (_orbit3 * yRot2) * _parentMat3 * (yRot3) * (_lastMat3 * yRot1) * _scaleMat2;
	GET_SINGLE(TransformManager).Bind(currMat, shaderID);
	_planet->Render();



}

void Ex19::MoveSystem(DIR dir)
{
	switch (dir)
	{
	case DIR_UP:
		_worldMat = _worldMat * GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.2f, 0.0f));
		break;
		
	case DIR_DOWN:
		_worldMat = _worldMat * GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, -0.2f, 0.0f));
		break;
		
	case DIR_LEFT:
		_worldMat = _worldMat * GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-0.2f, 0.0f, 0.0f));
		break;
		
	case DIR_RIGHT:
		_worldMat = _worldMat * GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.2f, 0.0f, 0.0f));
		break;
		
	case DIR_FRONT:
		_worldMat = _worldMat * GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 0.2f));
		break;
		
	case DIR_BACK:
		_worldMat = _worldMat * GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, -0.2f));
		break;



	}



}

void Ex19::PlayAnim()
{
	if (_yRotateAnim)
	{
		if(_yRotateDirection)
		{
			_yAnimMat = GET_SINGLE(TransformManager).GetRotateMatrix(_yAnimDeg, Y_AXIS);
			_yAnimDeg += 0.08f;
		}

		if(!_yRotateDirection)
		{
			_yAnimMat = GET_SINGLE(TransformManager).GetRotateMatrix(_yAnimDeg, Y_AXIS);
			_yAnimDeg -= 0.08f;
		}
	}
	
	if (_zRotateAnim)
	{
		if (_zRotateDirection)
		{
			_zAnimMat = GET_SINGLE(TransformManager).GetRotateMatrix(_zAnimDeg, Z_AXIS);
			_zAnimDeg += 0.05f;
		}

		if (!_zRotateDirection)
		{
			_zAnimMat = GET_SINGLE(TransformManager).GetRotateMatrix(_zAnimDeg, Z_AXIS);
			_zAnimDeg -= 0.05f;
		}
	}



}
