#include "pch.h"
#include "Ex26.h"
Ex26::Ex26()
{
	InitEx();
}

Ex26::~Ex26()
{
}

void Ex26::InitEx()
{
	_camera = new Camera(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
}

void Ex26::drawScene()
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

	KeyboardUpdate();
	AnimUpdate();

	Render();

	glutSwapBuffers();
	glutPostRedisplay();



}

void Ex26::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex26::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();
	if (ks == nullptr)
		return;

	switch (ks->key)
	{
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

	case 'r':
		if (lightRotAnim)
			lightRotAnim = false;
		else
			lightRotAnim = true;

		lightRotDir = true;
		break;
		
	case 'R':
		if (lightRotAnim)
			lightRotAnim = false;
		else
			lightRotAnim = true;

		lightRotDir = false;
		break;

	case 'q':
		exit(0);
		break;

	default:
		break;
	}



	delete ks;
}

void Ex26::Render()
{
	if (_sphere == nullptr)
	{
		MakePlanet();
		_light = new Light(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 0.0, _shaderID);
	}

	glEnable(GL_DEPTH_TEST);

	RenderPlanet();
	RenderLightObj();
}

void Ex26::AnimUpdate()
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
}

void Ex26::MakePlanet()
{
	_sphere = new Model("./../ex26_sphere.obj");
}

void Ex26::RenderPlanet()
{
	// 吝缴 青己 1
	unsigned int uniformLoc = glGetUniformLocation(_shaderID, "customColor");
	glUniform3f(uniformLoc, 1.0f, 0.0f, 0.0f);

	glm::mat4 scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.7f, 0.7f, 0.7f));
	GET_SINGLE(TransformManager).Bind(_worldMat * scale, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_sphere->GetVAO()[0]);


	// 青己 2
	glUniform3f(uniformLoc, 0.0f, 1.0f, 0.0f);

	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-5.0f, 0.0f, 0.0f));
	GET_SINGLE(TransformManager).Bind(_worldMat * move * scale, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_sphere->GetVAO()[0]);

	
	// 青己 3
	glUniform3f(uniformLoc, 0.0f, 0.0f, 1.0f);

	scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.3f, 0.3f, 0.3f));
	move = GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-9.0f, 0.0f, 0.0f));
	GET_SINGLE(TransformManager).Bind(_worldMat * move * scale, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_sphere->GetVAO()[0]);

}

void Ex26::RenderLightObj()
{
	unsigned int uniformLoc = glGetUniformLocation(_shaderID, "customColor");
	glUniform3f(uniformLoc, 1.0f, 1.0f, 1.0f);


	glm::mat4 scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.08f, 0.08f, 0.08f));
	glm::mat4 move = GET_SINGLE(TransformManager).GetTranslateMatrix(_light->getLightPos());
	GET_SINGLE(TransformManager).Bind(_worldMat * move * scale, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_sphere->GetVAO()[0]);

}