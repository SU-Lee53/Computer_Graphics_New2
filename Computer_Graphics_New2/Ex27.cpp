#include "pch.h"
#include "Ex27.h"

Ex27::Ex27()
{
	InitEx();
}

Ex27::~Ex27()
{
}

void Ex27::InitEx()
{
	_camera = new Camera(glm::vec3(0.0f, 50.0f, 50.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 100.0f, -5.0f);
}

void Ex27::drawScene()
{
	_deltaTime = GET_SINGLE(TimeManager).GetDeltaTime();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderID = GET_SINGLE(Core).GetTexShaderID();
	glUseProgram(_shaderID);
	_camera->Bind(_shaderID);
	_projection->Bind(_shaderID);
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);
	unsigned int viewPosLoc = glGetUniformLocation(_shaderID, "viewPos");
	glUniform3f(viewPosLoc, _camera->getCameraPos()[0], _camera->getCameraPos()[1], _camera->getCameraPos()[2]);

	if (_light != nullptr)
	{
		_light->Bind();
	}

	AnimUpdate();
	KeyboardUpdate();

	Render();

	glutSwapBuffers();
	glutPostRedisplay();



}

void Ex27::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex27::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();
	if (ks == nullptr)
		return;

	switch (ks->key)
	{
	case 'm':
		if (ambientSwitch)
		{
			ambientSwitch = false;
			_light->ChangeAmbientIntensity(0.1f);
		}
		else
		{
			ambientSwitch = true;
			_light->ChangeAmbientIntensity(0.3f);
		}

		break;

	case 'c':
		lightColorSwitch = (lightColorSwitch + 1) % 4;
		switch (lightColorSwitch)
		{
		case 0:
			lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		case 1:
			lightColor = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		case 2:
			lightColor = glm::vec3(0.0f, 1.0f, 0.0f);
			break;

		case 3:
			lightColor = glm::vec3(0.0f, 0.0f, 1.0f);
			break;
		}
		_light->ChangeLightColor(lightColor);

		break;

	case 'y':
		if (!lightRotAnim)
			lightRotAnim = true;

		if (lightRotDir)
			lightRotDir = false;
		else
			lightRotDir = true;

		break;

	case 's':
		if (lightRotAnim)
			lightRotAnim = false;

		break;


	case 'q':
		exit(0);
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

	case 't':
		if (craneMoveSwitch)
		{
			craneMoveSwitch = false;
		}
		else
		{
			craneMoveSwitch = true;
		}
		break;

	default:
		break;
	}



	delete ks;
}

void Ex27::AnimUpdate()
{
	if (lightRotAnim)
	{
		if (lightRotDir)
		{
			lightRotMat = GET_SINGLE(TransformManager).GetRotateMatrix(lightRotSpeed * _deltaTime, Y_AXIS);
			_light->lightTransform(lightRotMat);
		}
		else
		{
			lightRotMat = GET_SINGLE(TransformManager).GetRotateMatrix(-lightRotSpeed * _deltaTime, Y_AXIS);
			_light->lightTransform(lightRotMat);
		}
	}

	if(craneMoveSwitch)
	{
		craneMov = glm::sin(glm::radians(paramDeg)) * 10;
		paramDeg += 30 * _deltaTime;
		craneMoveMat = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(craneMov, 0.0f, 0.0f));
	}

}

void Ex27::Render()
{
	if (_floor == nullptr)
	{
		_floor = new Model("./../ex27_floor.obj");
		_upper = new Model("./../ex27_upper.obj");
		_lower = new Model("./../ex27_lower.obj");
		_light = new Light(glm::vec3(0.0f, 20.0f, 20.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.0, _shaderID);
	}

	glEnable(GL_DEPTH_TEST);

	RenderCrane(); 
	RenderLightObj();
}

void Ex27::RenderCrane()
{
	// ¹Ù´Ú
	unsigned int uniformLoc = glGetUniformLocation(_shaderID, "customColor");
	glUniform3f(uniformLoc, 1.0f, 1.0f, 0.0f);

	glm::mat4 scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.7f, 0.7f, 0.7f));
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_floor->GetVAO()[0]);


	// ¾Æ·§¸ö
	glUniform3f(uniformLoc, 0.0f, 1.0f, 0.0f);

	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-5.0f, 0.0f, 0.0f));
	GET_SINGLE(TransformManager).Bind(_worldMat * craneMoveMat * scale, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_lower->GetVAO()[0]);


	// À­¸ö
	glUniform3f(uniformLoc, 0.0f, 0.0f, 1.0f);

	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 0.5f, 0.5f));
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-9.0f, 0.0f, 0.0f));
	GET_SINGLE(TransformManager).Bind(_worldMat * craneMoveMat * scale, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_upper->GetVAO()[0]);
}

void Ex27::RenderLightObj()
{
	if (_lightObj == nullptr)
	{
		_lightObj = new Model("./../ex25_cube.obj");
	}
	unsigned int uniformLoc = glGetUniformLocation(_shaderID, "customColor");
	glUniform3f(uniformLoc, 1.0f, 1.0f, 1.0f);


	glm::mat4 scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.08f, 0.08f, 0.08f));
	glm::mat4 move = GET_SINGLE(TransformManager).GetTranslateMatrix(_light->getLightPos());
	GET_SINGLE(TransformManager).Bind(_worldMat * move * scale, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_lightObj->GetVAO()[0]);

}