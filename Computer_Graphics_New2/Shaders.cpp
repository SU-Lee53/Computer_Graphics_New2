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

	// ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	// filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
	// �� ���Ͽ����� Utills�� �Լ����� �� ���ǰ� �������

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

	// �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
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

	// �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
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

	// ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	// filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
	// �� ���Ͽ����� Utills�� �Լ����� �� ���ǰ� �������

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

	// �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
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

