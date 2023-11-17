#pragma once

class Shaders
{

public:
	Shaders();
	~Shaders();

	// 셰이더 컴파일 함수
	GLuint makeShaderProgram1();
	GLuint makeShaderProgram2();
	GLuint makeShaderProgram3();

	// 정점 버퍼 함수

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

