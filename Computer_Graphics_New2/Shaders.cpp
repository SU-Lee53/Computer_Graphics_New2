#include "pch.h"
#include "Shaders.h"
using namespace std;

Shaders::Shaders()
{
	makeShaderProgram1();
	makeShaderProgram2();
	makeShaderProgram3();
}

Shaders::~Shaders()
{
	glDeleteShader(shaderID);
	glDeleteShader(uShaderID);
	glDeleteShader(texShaderID);
}

void Shaders::makeVertexShaders()
{
	GLchar* vertexSource;

	// 버텍스 셰이더 읽어 저장하고 컴파일 하기
	// filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
	// 본 파일에서는 Utills에 함수선언 및 정의가 담겨있음

	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: Failed to compile vertex shader\n" << errorLog << endl;
		return;
	}
}

void Shaders::makeFragmentShaders()
{
	GLchar* fragmentSource;

	// 프래그먼트 셰이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("fragment.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: Failed to complie fragment shader\n" << errorLog << endl;
		return;
	}
}

void Shaders::makeUniformFragmentShader()
{
	GLchar* fragmentSource;

	// 프래그먼트 셰이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("uniformFragment.glsl");
	uniformShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(uniformShader, 1, &fragmentSource, NULL);
	glCompileShader(uniformShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(uniformShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(uniformShader, 512, NULL, errorLog);
		cerr << "ERROR: Failed to complie fragment shader\n" << errorLog << endl;
		return;
	}
}

void Shaders::makeTexVertexShader()
{
	GLchar* vertexSource;

	// 버텍스 셰이더 읽어 저장하고 컴파일 하기
	// filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
	// 본 파일에서는 Utills에 함수선언 및 정의가 담겨있음

	vertexSource = filetobuf("light_tex_vs.glsl");
	texVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(texVertexShader, 1, &vertexSource, NULL);
	glCompileShader(texVertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(texVertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(texVertexShader, 512, NULL, errorLog);
		cerr << "ERROR: Failed to compile vertex shader\n" << errorLog << endl;
		return;
	}
}

void Shaders::makeTexFragmentshader()
{
	GLchar* fragmentSource;

	// 프래그먼트 셰이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("light_tex_fs.glsl");
	texFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(texFragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(texFragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(texFragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(texFragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: Failed to complie fragment shader\n" << errorLog << endl;
		return;
	}
}

GLuint Shaders::makeShaderProgram1()
{
	
	makeVertexShaders();
	makeFragmentShaders();

	shaderID = glCreateProgram();

	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		cerr << "ERROR: Failed to link shader program\n" << errorLog << endl;
		return false;
	}

	return shaderID;

}

GLuint Shaders::makeShaderProgram2()
{
	makeVertexShaders();
	makeUniformFragmentShader();

	uShaderID = glCreateProgram();

	glAttachShader(uShaderID, vertexShader);
	glAttachShader(uShaderID, uniformShader);

	glLinkProgram(uShaderID);

	glDeleteShader(vertexShader);
	glDeleteShader(uniformShader);

	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(uShaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(uShaderID, 512, NULL, errorLog);
		cerr << "ERROR: Failed to link shader program\n" << errorLog << endl;
		return false;
	}

	return uShaderID;

}

GLuint Shaders::makeShaderProgram3()
{
	makeTexVertexShader();
	makeTexFragmentshader();

	texShaderID = glCreateProgram();

	glAttachShader(texShaderID, texVertexShader);
	glAttachShader(texShaderID, texFragmentShader);

	glLinkProgram(texShaderID);

	glDeleteShader(texVertexShader);
	glDeleteShader(texFragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetProgramiv(texShaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(texShaderID, 512, NULL, errorLog);
		cerr << "ERROR: Failed to link shader program\n" << errorLog << endl;
		return false;
	}

	return texShaderID;
}

