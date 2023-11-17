
#include "pch.h"
#include "Utills.h"


Coord AdjustMouseCoordinate(Coord coord)
{
	GLint width = glutGet(GLUT_WINDOW_WIDTH);
	GLint height = glutGet(GLUT_WINDOW_HEIGHT);

	coord.x = (coord.x - (width / 2)) / (width / 2);
	coord.y = -1 * (coord.y - (height / 2)) / (height / 2);

	return coord;
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;

	return buf;
}

Coord GetRandomCoord()
{
	Coord pos;
	pos.x = static_cast<float>(rand()) / (RAND_MAX / 2) - 1.0f;
	pos.y = static_cast<float>(rand()) / (RAND_MAX / 2) - 1.0f;
	pos.z = static_cast<float>(rand()) / (RAND_MAX / 2) - 1.0f;

	return pos;
}

RGB GetRandomRGB()
{
	RGB rgb;
	rgb.Red = static_cast<float>(rand()) / RAND_MAX;
	rgb.Green = static_cast<float>(rand()) / RAND_MAX;
	rgb.Blue = static_cast<float>(rand()) / RAND_MAX;

	return rgb;
}

void DrawUniformAxis(float length)
{
	glUseProgram(GET_SINGLE(Core).GetuShaderID());
	unsigned int uLocation = glGetUniformLocation(GET_SINGLE(Core).GetuShaderID(), "uniformColor");

	// x��
	float color1[] = { 1.0f, 0.0f, 0.0f };
	glUniform3fv(uLocation, 1, color1);
	glBegin(GL_LINES);
	glLineWidth(3.0f);
	glVertex3f(-length, 0.0, 0.0);
	glVertex3f(length, 0.0, 0.0);
	glEnd();

	// y��
	float color2[] = { 0.0f, 1.0f, 0.0f };
	glUniform3fv(uLocation, 1, color2);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0, -length, 0.0);
	glVertex3f(0.0, length, 0.0);
	glEnd();

	// z��
	float color3[] = { 0.0f, 0.0f, 1.0f };
	glUniform3fv(uLocation, 1, color3);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0, 0.0, -length);
	glVertex3f(0.0, 0.0, length);
	glEnd();




}

void DrawAxis(float length)
{
	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-length, 0.0, 0.0);
	glVertex3f(length, 0.0, 0.0);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0, -length, 0.0);
	glVertex3f(0.0, length, 0.0);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0, 0.0, -length);
	glVertex3f(0.0, 0.0, length);

	glEnd();
}

void SetBackground(RGB rgb)
{
	glClearColor(rgb.Red, rgb.Green, rgb.Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
