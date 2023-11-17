#include "pch.h"
#include "Ex20.h"

Ex20::Ex20()
{
	InitEx();
}

Ex20::~Ex20()
{
}

void Ex20::InitEx()
{
	cout << "b / B: ũ������ �Ʒ� ��ü�� x�� �������� �� / �� �������� �̵��Ѵ�.�ٽ� ������ �����.								" << endl;
	cout << "	�Ʒ� ��ü�� �̵��ϸ� �߾� ��ü�� �� ���� ���� ���� �̵��Ѵ�.													" << endl;
	cout << "m / M : ũ������ �߾� ��ü�� y�࿡ ���Ͽ� �� / �� �������� ȸ���Ѵ�.�ٽ� ������ �����.							" << endl;
	cout << "	�߾� ��ü�� ȸ���ϸ� �� ���� �ȵ� ���� ȸ���Ѵ�.																" << endl;
	cout << "f / F : ������ y�࿡ ���Ͽ� �� / �� �������� ȸ���ϴµ�, �� ������ ���� �ݴ�������� ȸ���Ѵ�.�ٽ� ������ �����.	" << endl;
	cout << "e / E : 2�� ������ ���ݾ� �̵��ؼ� �� ���� �ȴ� / �ٽ� ���ڸ��� �̵��ؼ� 2���� �ȴ�.								" << endl;
	cout << "	������ ȸ���Ǿ� �ִٸ�, ���� �ڸ����� ȸ���� �� �̵��Ѵ�.														" << endl;
	cout << "t / T : ũ������ �� �� 2���� ���� z�࿡ ���Ͽ� �� / �� �������� ���� �ݴ�������� ȸ���Ѵ�.�ٽ� ������ �����.		" << endl;
	cout << "	ȸ�� ������ - 90 ~90�� ���̷� ���Ѵ�.																			" << endl;
	cout << "ī�޶� ��ȯ																										" << endl;
	cout << "z / Z : ī�޶� z�� �� / �� �������� �̵�																			" << endl;
	cout << "x / X : ī�޶� x�� �� / �� �������� �̵�																			" << endl;
	cout << "y / Y : ī�޶� ���� y�࿡ ���Ͽ� ȸ��																				" << endl;
	cout << "r / R : ȭ���� �߽��� y�࿡ ���Ͽ� ī�޶� ȸ��(������ ���Ͽ� ����)												" << endl;
	cout << "a / A : r ��ɾ�� ���� ȭ���� �߽��� �࿡ ���Ͽ� ī�޶� ȸ���ϴ� �ִϸ��̼��� �����Ѵ� / �����.				" << endl;
	cout << "s / S : ��� ������ ���߱�																							" << endl;
	cout << "c / C : ��� �������� �ʱ�ȭ�ȴ�.																					" << endl;
	cout << "Q : ���α׷� �����ϱ�																								" << endl;

	_camera = new Camera(glm::vec3(-2.0, 2.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
}

void Ex20::drawScene()
{
	_shaderID = GET_SINGLE(Core).GetShaderID();
	glUseProgram(_shaderID);

	_projection->Bind(_shaderID);
	_camera->Bind(_shaderID);
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);

	KeyboardUpdate();
	PlayCraneAnim();
	PlayCameraAnim();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawAxis(2.0f);
	Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Ex20::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex20::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();
	if (ks == nullptr)
		return;

	switch (ks->key)
	{
	case 'b':
		if (!_xMoveAllAnim)
			_xMoveAllAnim = true;
		else
			_xMoveAllAnim = false;

		_xMoveAllDir = true;

		break;
		
	case 'B':
		if (!_xMoveAllAnim)
			_xMoveAllAnim = true;
		else
			_xMoveAllAnim = false;

		_xMoveAllDir = false;

		break;
		
	case 'm':
		if (!_yRotUpperAnim)
			_yRotUpperAnim = true;
		else
			_yRotUpperAnim = false;

		_yRotUpperDir = true;

		break;
		
	case 'M':
		if (!_yRotUpperAnim)
			_yRotUpperAnim = true;
		else
			_yRotUpperAnim = false;

		_yRotUpperDir = false;

		break;
		
	case 'f':
		if (!_yRotBarrelAnim)
			_yRotBarrelAnim = true;
		else
			_yRotBarrelAnim = false;

		_yRotBarrelDir = true;

		break;
		
	case 'F':
		if (!_yRotBarrelAnim)
			_yRotBarrelAnim = true;
		else
			_yRotBarrelAnim = false;

		_yRotBarrelDir = false;

		break;
		
	case 'e':
		if (!_xMoveDBarrelAnim)
			_xMoveDBarrelAnim = true;
		else
			_xMoveDBarrelAnim = false;

		_xMoveDBarrelDir = true;

		break;
		
	case 'E':
		if (!_xMoveDBarrelAnim)
			_xMoveDBarrelAnim = true;
		else
			_xMoveDBarrelAnim = false;

		_xMoveDBarrelDir = false;

		break;
		
	case 't':
		if (!_zRotArmAnim)
			_zRotArmAnim = true;

		break;
		
	case 'T':
		if (_zRotArmAnim)
			_zRotArmAnim = false;

		break;

	case 'x':
		_camera->CameraMove(glm::vec3(-_camXMove, 0.0f, 0.0f));
		_camXDist -= _camXMove;
		break;

	case 'X':
		_camera->CameraMove(glm::vec3(_camXMove, 0.0f, 0.0f));
		_camXDist += _camXMove;
		break;
		
	case 'z':
		_camera->CameraMove(glm::vec3(0.0f, 0.0f, _camZMove));
		_camZDist += _camZMove;
		break;

	case 'Z':
		_camera->CameraMove(glm::vec3(0.0f, 0.0f, -_camZMove));
		_camZDist -= _camZMove;
		break;
		
	case 'y':
		_camYRev += 3.0f;
		_camYRot += 3.0f;
		_camera->CameraRotation(_camYRot, Y_AXIS);
		break;

	case 'Y':
		_camYRev -= 3.0f;
		_camYRot -= 3.0f;
		_camera->CameraRotation(_camYRot, Y_AXIS);
		break;

	case 'r':
		_camYRev += 3.0f;
		_camYRot += 3.0f;
		_camera->CameraRevolution(_camYRev, Y_AXIS);
		break;

	case 'R':
		_camYRev -= 3.0f;
		_camYRot -= 3.0f;
		_camera->CameraRevolution(_camYRev, Y_AXIS);
		break;
		
	case 'a':
		_camYRevAnim = true;
		break;
		
	case 'A':
		_camYRevAnim = false;
		break;


	case 's':
		cout << "All Anim Started" << endl;
		AnimPlayAll = true;
		break;
		
	case 'S':
		cout << "All Anim Stopped" << endl;
		AnimPlayAll = false;
		break;

	case 'c':
		ResetAll();
		break;


	case 'Q':
		exit(0);
		break;
	}

	delete ks;
}

void Ex20::PlayCraneAnim()
{

	if(AnimPlayAll)
	{
		if (_xMoveAllAnim)
		{
			_xMoveAll = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_xDistAll, 0.0f, 0.0f));
			if (_xMoveAllDir)
			{
				_xDistAll += 0.001f;
			}
			else
			{
				_xDistAll -= 0.001f;
			}
		}

		if (_yRotUpperAnim)
		{
			_yRotUpper = GET_SINGLE(TransformManager).GetRotateMatrix(_yDegUpper, Y_AXIS);
			if (_yRotUpperDir)
			{
				_yDegUpper += 0.05f;
			}
			else
			{
				_yDegUpper -= 0.05f;
			}
		}

		if (_yRotBarrelAnim)
		{
			_yRotBarrelLeft = GET_SINGLE(TransformManager).GetRotateMatrix(_yDegBarrelLeft, Y_AXIS);
			_yRotBarrelRight = GET_SINGLE(TransformManager).GetRotateMatrix(_yDegBarrelRight, Y_AXIS);
			if (_yRotBarrelDir)
			{
				_yDegBarrelLeft -= 0.1f;
				_yDegBarrelRight += 0.1f;
			}
			else if (!_yRotBarrelDir)
			{
				_yDegBarrelLeft += 0.1f;
				_yDegBarrelRight -= 0.1f;
			}

			if (_yDegBarrelLeft < -360.0f || _yDegBarrelLeft > 360.0f)
			{
				_yDegBarrelLeft = 0.0f;
				_yDegBarrelRight = 0.0f;
			}
			// if (_yRotBarrelDir && _yDegBarrelLeft >= -90.0f)
			// {
			// 	_yDegBarrelLeft -= 0.1f;
			// 	_yDegBarrelRight += 0.1f;
			// }
			// else if (_yRotBarrelDir && _yDegBarrelLeft < -90.0f)
			// {
			// 	_yRotBarrelAnim = false;
			// }
			// 
			// if (!_yRotBarrelDir && _yDegBarrelLeft <= 0.0f)
			// {
			// 	_yDegBarrelLeft += 0.1f;
			// 	_yDegBarrelRight -= 0.1f;
			// }
			// else if (!_yRotBarrelDir && _yDegBarrelLeft > 0.0f)
			// {
			// 	_yRotBarrelAnim = false;
			// }
		}

		if (_xMoveDBarrelAnim)
		{
			// ������ �����ִٸ� �ϴ� ����
			if (_yRotBarrelAnim)
			{
				_yRotBarrelAnim = false;
			}
			// �켱 ������ �����ڸ��� ��������
			if (_yDegBarrelLeft <= 0)
			{
				_yDegBarrelLeft += 0.1f;
				_yDegBarrelRight -= 0.1f;
				_yRotBarrelLeft = GET_SINGLE(TransformManager).GetRotateMatrix(_yDegBarrelLeft, Y_AXIS);
				_yRotBarrelRight = GET_SINGLE(TransformManager).GetRotateMatrix(_yDegBarrelRight, Y_AXIS);
			}
			else
			{
				_xMoveBarrelLeft = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_xDistBarrelLeft, 0.0f, 0.0f));
				_xMoveBarrelRight = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(_xDistBarrelRight, 0.0f, 0.0f));

				if (_xMoveDBarrelDir && _xDistBarrelLeft <= 0.7)
				{
					_xDistBarrelLeft += 0.005f;
					_xDistBarrelRight -= 0.005f;
				}
				else if (_xMoveDBarrelDir && _xDistBarrelLeft > 0.7)
				{
					_xMoveDBarrelAnim = false;
				}

				if (!_xMoveDBarrelDir && _xDistBarrelLeft >= 0.0)
				{
					_xDistBarrelLeft -= 0.005f;
					_xDistBarrelRight += 0.005f;
				}
				else if (!_xMoveDBarrelDir && _xDistBarrelLeft < 0.0)
				{
					_xMoveDBarrelAnim = false;
				}
			}

		}

		if (_zRotArmAnim)
		{
			_zRotArmLeft = GET_SINGLE(TransformManager).GetRotateMatrix(_zDegArmLeft, X_AXIS);
			_zRotArmRight = GET_SINGLE(TransformManager).GetRotateMatrix(_zDegArmRight, X_AXIS);

			if (_zRotArmDir && _zDegArmLeft <= 90.0f)
			{
				_zDegArmLeft += 0.05f;
				_zDegArmRight -= 0.05f;
			}
			else if (_zRotArmDir && _zDegArmLeft > 90.0f)
			{
				_zRotArmDir = false;
			}


			if (!_zRotArmDir && _zDegArmLeft >= -90.0f)
			{
				_zDegArmLeft -= 0.05f;
				_zDegArmRight += 0.05f;
			}
			else if (!_zRotArmDir && _zDegArmLeft < -90.0f)
			{
				_zRotArmDir = true;
			}
		}
	}


}

void Ex20::PlayCameraAnim()
{
	if(AnimPlayAll)
	{
		if (_camYRevAnim)
		{
			_camYRot += 0.1f;
			_camYRev += 0.1f;
			_camera->CameraRevolution(_camYRev, Y_AXIS);
		}
	}

}

void Ex20::Render()
{
	if (_floor == nullptr)
	{
		_floor = new Objects(OBJ_PLANE_RECT, { 0, 0, 0 }, 3.0f);
		MakeCrane();
		SetCraneMatrix();
	}

	glEnable(GL_DEPTH_TEST);

	_floor->Render();
	RenderCrane();

}

void Ex20::MakeCrane()
{
	_crane[0] = new Objects(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.7f);
	_crane[0]->ChangeColor({ 1.0f, 0.0f, 0.0f });

	_crane[1] = new Objects(-0.5f, 0.5f, 0.5f, -0.5f, 0.7f, 1.1f);
	_crane[1]->ChangeColor({ 0.0f, 1.0f, 0.0f });

	_crane[2] = new Objects(-0.8f, 1.0f, -0.6f, 2.0f, 0.1f, 0.3f);
	_crane[3] = new Objects(0.6f, 1.0f, 0.8f, 2.0f, 0.1f, 0.3f);
	_crane[2]->ChangeColor({ 0.0f, 0.0f, 1.0f });
	_crane[3]->ChangeColor({ 1.0f, 1.0f, 0.0f });

	_crane[4] = new Objects(-0.4f, -0.1f, -0.2f, 0.1f, 1.1f, 2.0f);
	_crane[5] = new Objects(0.2f, -0.1f, 0.4f, 0.1f, 1.1f, 2.0f);
	_crane[4]->ChangeColor({ 0.0f, 1.0f, 1.0f });
	_crane[5]->ChangeColor({ 1.0f, 0.0f, 1.0f });
}

void Ex20::SetCraneMatrix()
{

	Coord center = _crane[4]->GetCenter();
	_armLeft = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(center.x, 1.1f, center.z));
	
	center = _crane[5]->GetCenter();
	_armRight = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(center.x, 1.1f, center.z));
	
	center = _crane[4]->GetCenter();
	_armLeft2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-center.x, -1.1f, -center.z));
	
	center = _crane[5]->GetCenter();
	_armRight2 = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-center.x, -1.1f, -center.z));

}

void Ex20::RenderCrane()
{
	// �Ʒ���
	GET_SINGLE(TransformManager).Bind(_worldMat * _xMoveAll, _shaderID);
	_crane[0]->Render();

	// ����
	GET_SINGLE(TransformManager).Bind(_worldMat * _xMoveAll * _yRotUpper, _shaderID);
	_crane[1]->Render();

	// �Ʒ� ���� ��,��
	GET_SINGLE(TransformManager).Bind(_worldMat * _xMoveAll * _yRotBarrelLeft * _xMoveBarrelLeft, _shaderID);
	_crane[2]->Render();
	GET_SINGLE(TransformManager).Bind(_worldMat * _xMoveAll * _yRotBarrelRight * _xMoveBarrelRight, _shaderID);
	_crane[3]->Render();

	// �� ���� ��,��
	GET_SINGLE(TransformManager).Bind(_worldMat * _xMoveAll * _yRotUpper * (_armLeft * _zRotArmLeft * _armLeft2), _shaderID);
	_crane[4]->Render();
	GET_SINGLE(TransformManager).Bind(_worldMat * _xMoveAll * _yRotUpper * (_armRight * _zRotArmRight * _armRight2), _shaderID);
	_crane[5]->Render();
}

void Ex20::ResetAll()
{
	_xMoveAll = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
	_xDistAll = 0.0f;

	_yRotUpper = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, Y_AXIS);
	_yDegUpper = 0.0f;

	_yRotBarrelLeft = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, Y_AXIS);
	_yRotBarrelRight = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, Y_AXIS);
	_yDegBarrelLeft = 0.0f;
	_yDegBarrelRight = 0.0f;

	_xMoveBarrelLeft = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
	_xMoveBarrelRight = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(0.0f, 0.0f, 0.0f));
	_xDistBarrelLeft = 0.0f;
	_xDistBarrelRight = 0.0f;

	_zRotArmLeft = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
	_zRotArmRight = GET_SINGLE(TransformManager).GetRotateMatrix(0.0f, X_AXIS);
	_zDegArmLeft = 0.0f;
	_zDegArmRight = 0.0f;
	_zRotArmDir = true;

	_camera->CameraMove(glm::vec3(-_camXDist, 0.0f, 0.0f));
	_camXDist = 0.0f;
	
	_camera->CameraMove(glm::vec3(0.0f, 0.0f, -_camZDist));
	_camZDist = 0.0f;

	_camYRev = -45.0f;
	_camera->CameraRevolution(_camYRev, Y_AXIS);

	_camYRot = 90.0f + 45.0f;
	_camera->CameraRotation(_camYRot, Y_AXIS);
	
	_camera->ResetCamera(glm::vec3(-2.0, 2.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));


}

