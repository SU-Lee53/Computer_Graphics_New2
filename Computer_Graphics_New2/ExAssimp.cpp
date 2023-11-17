#include "pch.h"
#include "ExAssimp.h"

ExAssimp::ExAssimp()
{
}

ExAssimp::~ExAssimp()
{
}

void ExAssimp::InitEx()
{
	_camera = new Camera(glm::vec3(0.0, 4.0, 10.0), glm::vec3(0.0, 4.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
	modelTest = new Model(".\..\weirdSphere.obj");
}

void ExAssimp::drawScene()
{
	_shaderID = GET_SINGLE(Core).GetShaderID();
	glUseProgram(_shaderID);
	_camera->Bind(_shaderID);
	_projection->Bind(_shaderID);
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);



}

void ExAssimp::Reshape(int w, int h)
{
}
