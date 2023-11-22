#include "pch.h"
#include "Ex25.h"

Ex25::Ex25()
{
	InitEx();
}

Ex25::~Ex25()
{
}

void Ex25::InitEx()
{
	_camera = new Camera(glm::vec3(10.0, 10.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
}

void Ex25::drawScene()
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

	DrawAxis(8.0f);

	if(_light != nullptr)
	{
		_light->Bind();
	}

	float lightpos[3];
	float viewpos[3];
	glGetUniformfv(_shaderID, glGetUniformLocation(_shaderID, "lightPos"), lightpos);
	glGetUniformfv(_shaderID, glGetUniformLocation(_shaderID, "viewPos"), viewpos);

	// cout << lightpos[0] << ", " << lightpos[1] << ", " << lightpos[2] << endl;
	// cout << viewpos[0] << ", " << viewpos[1] << ", " << viewpos[2] << endl;

	KeyboardUpdate();
	AnimationUpdate();

	Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void Ex25::Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Ex25::KeyboardUpdate()
{
	KeyboardState* ks = GET_SINGLE(InputManager).DequeueKeyboardBuf();
	if (ks == nullptr)
		return;

	switch (ks->key)
	{
	case 'n':
		if (drawMode)
			drawMode = false;
		else
			drawMode = true;
		break;

	case 'y':
		if (rotAnim)
			rotAnim = false;
		else
			rotAnim = true;
		break;
		
	case 'r':
		if (lightRotAnim)
			lightRotAnim = false;
		else
			lightRotAnim = true;
		break;

	case 'z':
		if(_light->getLightPos()[0] >= 0.0f)
			_light->lightTransform(GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-1.0f, 0.0f, 0.0f)) * lightRotMat);
		else
			_light->lightTransform(GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(1.0f, 0.0f, 0.0f)) * lightRotMat);

		MakeLightOrbit();
		break;

	case 'Z':
		if (_light->getLightPos()[0] >= 0.0f)
			_light->lightTransform(GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(1.0f, 0.0f, 0.0f)) * lightRotMat);
		else
			_light->lightTransform(GET_SINGLE(TransformManager).GetTranslateMatrix(glm::vec3(-1.0f, 0.0f, 0.0f)) * lightRotMat);

		MakeLightOrbit();
		break;

	default:
		break;
	}



	delete ks;
}

void Ex25::AnimationUpdate()
{
	if (rotAnim)
	{
		_objRotMat = GET_SINGLE(TransformManager).GetRotateMatrix(rotDeg, Y_AXIS);
		rotDeg += rotSpeed * _deltaTime;
	}

	if (lightRotAnim)
	{
		lightRotMat = GET_SINGLE(TransformManager).GetRotateMatrix(lightRotSpeed * _deltaTime, Y_AXIS);
		_light->lightTransform(lightRotMat);
	}


}

void Ex25::MakeLightOrbit()
{
	// 우선 정점 벡터를 지움
	_orbitvBuf.clear();
	_orbitvBuf.shrink_to_fit();

	// 조명과 중심점 사이 거리 계산
	float distance = sqrt(pow(_light->getLightPos()[0], 2) + pow(_light->getLightPos()[2], 2));

	float degree = 0.0f;
	int idx = 0;
	while (degree <= 360.0f)
	{
		glm::vec3 pos = glm::vec3(0.0f);
		pos[0] = distance * glm::cos(glm::radians(degree));
		pos[1] = _light->getLightPos()[1];
		pos[2] = distance * glm::sin(glm::radians(degree));

		_orbitvBuf.push_back(pos);

		degree += 10.0f;
		idx += 3;
	}

}

void Ex25::Render()
{
	if (_cube == nullptr)
	{
		_cube = new Model("./../ex25_cube.obj");
		_pyramid = new Model("./../ex25_pyramid.obj");
		_light = new Light(glm::vec3(8.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3, 0.0, _shaderID);
		MakeLightOrbit();
	}

	glEnable(GL_DEPTH_TEST);


	unsigned int uniformLoc = glGetUniformLocation(_shaderID, "customColor");
	glUniform3f(uniformLoc, _objColor.Red, _objColor.Green, _objColor.Blue);

	glm::mat4 scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.2f, 0.2f, 0.2f));
	GET_SINGLE(TransformManager).Bind(_worldMat * scale * _objRotMat, _shaderID);

	if(drawMode)
		GET_SINGLE(Renderer).RenderModel(_cube->GetVAO()[0]);
	else
		GET_SINGLE(Renderer).RenderModel(_pyramid->GetVAO()[0]);


	RenderLightObj();
	RenderLightOrbit();
}

void Ex25::RenderLightObj()
{
	unsigned int uniformLoc = glGetUniformLocation(_shaderID, "customColor");
	glUniform3f(uniformLoc, _lightobjColor.Red, _lightobjColor.Green, _lightobjColor.Blue);


	glm::mat4 scale = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.05f, 0.05f, 0.05f));
	glm::mat4 move = GET_SINGLE(TransformManager).GetTranslateMatrix(_light->getLightPos());
	GET_SINGLE(TransformManager).Bind(_worldMat * move * scale, _shaderID);
	GET_SINGLE(Renderer).RenderModel(_cube->GetVAO()[0]);

}

void Ex25::RenderLightOrbit()
{

	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);

	glBegin(GL_LINES);

	unsigned int uniformLoc = glGetUniformLocation(_shaderID, "customColor");
	glUniform3f(uniformLoc, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < _orbitvBuf.size() - 1; i++)
	{
		glVertex3f(_orbitvBuf.at(i)[0], _orbitvBuf.at(i)[1], _orbitvBuf.at(i)[2]);
		glVertex3f(_orbitvBuf.at(i + 1)[0], _orbitvBuf.at(i + 1)[1], _orbitvBuf.at(i + 1)[2]);
	}

	glEnd();
}

