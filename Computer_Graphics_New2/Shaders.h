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

private:
	void makeVertexShaders();
	void makeFragmentShaders();
	void makeUniformFragmentShader();

	void makeTexVertexShader();
	void makeTexFragmentshader();

private:
	GLuint shaderID;
	GLuint uShaderID;
	GLuint texShaderID;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint uniformShader;

	GLuint texVertexShader;
	GLuint texFragmentShader;
	
};

