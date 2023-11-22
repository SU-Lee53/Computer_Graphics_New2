#include "pch.h"
#include "ExAssimp.h"

ExAssimp::ExAssimp()
{
	InitEx();
}

ExAssimp::~ExAssimp()
{
}

void ExAssimp::InitEx()
{
	_camera = new Camera(glm::vec3(0.0, 5.0, 10.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	_projection = new Projection(45.0f, 1.0f, 0.1f, 50.0f, -5.0f);
}

void ExAssimp::drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_shaderID = GET_SINGLE(Core).GetTexShaderID();
	glUseProgram(_shaderID);
	_camera->Bind(_shaderID);
	_projection->Bind(_shaderID);
	GET_SINGLE(TransformManager).Bind(_worldMat, _shaderID);


	Render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void ExAssimp::Reshape(int w, int h)
{
}

void ExAssimp::Render()
{

	if (modelTest == nullptr)
	{
		modelTest = new Model("./../teapot.obj");
	}


	glEnable(GL_DEPTH_TEST);


	unsigned int uniformLoc = glGetUniformLocation(_shaderID, "customColor");

	vector<VAO*> temp = modelTest->GetVAO();
	for (int i = 0; i < temp.size(); i++)
	{

		glUniform3f(uniformLoc, 1.0f, 1.0f, 0.0f);
		glm::mat4 matTemp = GET_SINGLE(TransformManager).GetScaleMatrix(glm::vec3(0.3f, 0.3f, 0.3f));

		GET_SINGLE(TransformManager).Bind(_worldMat * matTemp, _shaderID);
		GET_SINGLE(Renderer).RenderModel(temp.at(i));
	}

}
