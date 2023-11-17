#pragma once

class Shaders
{

public:
	Shaders();
	~Shaders();

	// ���̴� ������ �Լ�
	GLuint makeShaderProgram1();
	GLuint makeShaderProgram2();
	GLuint makeShaderProgram3();

	// ���� ���� �Լ�

	int GetShaderID() { return shaderID; }
	int GetuShaderID() { return uShaderID; }
	int GetMultipleViewportShaderID() { return mvPortID; }

private:
	void makeVertexShaders();
	void makeFragmentShaders();

	void makeUniformFragmentShader();
	void makeMViewportShader();

private:
	GLuint shaderID;
	GLuint uShaderID;
	GLuint mvPortID;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint uniformShader;
	GLuint mvPortShader;
	
};

