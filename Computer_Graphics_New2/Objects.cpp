#include "pch.h"
#include "Objects.h"
#include <cmath>

Objects::Objects(OBJ_TYPE_2D type, Coord pos, float size) : _centerPos(pos), _size(size)
{
	CreateObject2D(type);
}

Objects::Objects(OBJ_TYPE_3D type, Coord pos, float size) : _centerPos(pos), _size(size)
{
	CreateObject3D(type);
}

Objects::Objects(OBJ_TYPE_3D type, Coord pos, float size, VAO_TYPE indexType) : _centerPos(pos), _size(size), _indexType(indexType)
{
	if(_indexType == NON_INDEXED)
		CreateNonIndexedObject3D(type);
	else
		CreateObject3D(type);
}

Objects::Objects(QOBJ_TYPE type, Coord pos, float size, GLenum drawType, RGB rgb) 
	: _qType(type), _centerPos(pos), _size(size), _drawType(drawType), _rgb(rgb)
{
	CreateQuadricObject(drawType);
}

Objects::Objects(float left, float top, float right, float bottom, float floorHeight, float height)
{
	Coord center;
	center.x = (right + left) / 2;
	center.y = (height + floorHeight) / 2;
	center.z = (top + bottom) / 2;


	_centerPos = center;

	CreateCubeUsingParams(left, top, right, bottom, floorHeight, height);

}

Objects::~Objects()
{
	if (isQuadric() == false)
		_vao->~VAO();
}

void Objects::CreateObject2D(OBJ_TYPE_2D type)
{
	switch (type)
	{
	case OBJ_LINE:


	case OBJ_TRIANGLE:
	{
		float vertex[] = {
			_centerPos.x, _centerPos.y + (_size * 2), 0.0f,
			_centerPos.x - _size, _centerPos.y - _size, 0.0f,
			_centerPos.x + _size, _centerPos.y - _size, 0.0f
		};
		float color[] = {
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
		};
		_vao = new VAO(vertex, color, 9);
		_indexType = INDEXED;
	}
		break;
	}
}

void Objects::CreateObject3D(OBJ_TYPE_3D type)
{
	switch (type)
	{
	case OBJ_TETRAHEDRON:
	{
		float vertex[] = 
		{		// 사면체의 정점: 4*3 = 12, 위에 꼭짓점 하나 찍고 zx평면에 삼각형 하나 그려서 정점 이어주면 됨
			_centerPos.x, _centerPos.y + (_size * sqrt(2)), _centerPos.z,	// 위쪽 꼭짓점
			_centerPos.x, _centerPos.y - _size, _centerPos.z - (_size * sqrt(2)),
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
		};
		float color[] = 
		{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f
		};
		unsigned int element[] = 
		{
			0, 2, 1,
			0, 3, 2,
			0, 1, 3,
			1, 2, 3
		};
		_vao = new VAO(vertex, color, element, 12, 12);
		_indexType = INDEXED;
		break;
	}
	case OBJ_CUBE:
	{
		float vertex[] = 
		{
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size
		};
		float color[] = 
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f
		};
		unsigned int element[] = 
		{
			0, 2, 1,	// 면 1
			1, 2, 3,
			0, 4, 2,	// 면 2
			2, 4, 6,
			2, 6, 3,	// 면 3
			3, 6, 7,
			1, 3, 5,	// 면 4
			3, 7, 5,
			0, 1, 4,	// 면 5
			1, 5, 4,
			6, 4, 5,	// 면 6
			6, 5, 7
		};
		_vao = new VAO(vertex, color, element, 24, 36);
		_indexType = INDEXED;
		break;
	}

	case OBJ_PYRAMID:
	{
		float vertex[] = 
		{
			_centerPos.x, _centerPos.y + _size, _centerPos.z,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size
		};
		float color[] = 
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f
		};
		unsigned int element[] = 
		{
			0, 2, 1,
			0, 1, 3,
			0, 3, 4,
			0, 4, 2,
			1, 2, 3,
			2, 4, 3
		};
		_vao = new VAO(vertex, color, element, 15, 18);
		_indexType = INDEXED;
		break;
	}

	case OBJ_PLANE_RECT:	// 기본적으로 zx평면위에 만듬
	{
		float vertex[] =
		{
			_centerPos.x - _size, _centerPos.y, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y, _centerPos.z + _size
		};
		float color[] =
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f,
		};
		unsigned int element[] =
		{
			0, 1, 2,
			0, 2, 3
		};
		_vao = new VAO(vertex, color, element, 12, 6);
		_indexType = INDEXED;
		break;
	}

	case OBJ_PLANE_TRIANGLE:	// 기본적으로 zx평면위에 만듬
	{
		float vertex[] = // 한 변의 길이가 2 * _size인 정삼각형
		{
			_centerPos.x, _centerPos.y, _centerPos.z - _size,	// 상단
			_centerPos.x - _size, _centerPos.y, _centerPos.z + _size,	// 좌하단
			_centerPos.x + _size, _centerPos.y, _centerPos.z + _size	// 우하단
		};
		float color[] =
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
		};
		_vao = new VAO(vertex, color, 9);
		_indexType = NON_INDEXED;
		break;
	}


	}

}

void Objects::CreateNonIndexedObject3D(OBJ_TYPE_3D type)
{
	switch (type)
	{
	case OBJ_CUBE:
	{
		float vertex[] =
		{
			// _centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,	0
			// _centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,	1
			// _centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,	2
			// _centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,	3
			// _centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,	4
			// _centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,	5
			// _centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,	6
			// _centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size		7

			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,	// 윗면		0, 2, 1 / 1, 2, 3 
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,

			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,	// 왼쪽면	0, 4, 2 / 2, 4, 6
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,	
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,

			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z + _size,	// 앞면		2, 6, 3 / 3, 6, 7
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,

			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,	// 오른쪽면	1, 3, 5 / 5, 3, 7
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,

			_centerPos.x - _size, _centerPos.y + _size, _centerPos.z - _size,	// 뒷면		0, 1, 4 / 1, 5, 4
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y + _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,

			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z - _size,	// 아랫면	4, 5, 6	/ 5, 7, 6
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z - _size,
			_centerPos.x + _size, _centerPos.y - _size, _centerPos.z + _size,
			_centerPos.x - _size, _centerPos.y - _size, _centerPos.z + _size
		};

		glm::vec3 c0 = glm::vec3 (1.0f, 0.0f, 0.0f);
		glm::vec3 c1 = glm::vec3 (0.0f, 1.0f, 0.0f);
		glm::vec3 c2 = glm::vec3 (0.0f, 0.0f, 1.0f);
		glm::vec3 c3 = glm::vec3 (1.0f, 1.0f, 0.0f);

		glm::vec3 c4 = glm::vec3 (0.0f, 1.0f, 1.0f);
		glm::vec3 c5 = glm::vec3 (1.0f, 0.0f, 1.0f);
		glm::vec3 c6 = glm::vec3 (0.0f, 0.0f, 0.0f);
		glm::vec3 c7 = glm::vec3 (1.0f, 1.0f, 1.0f);

		float color[] =
		{
			// 1.0f, 0.0f, 0.0f,	0
			// 0.0f, 1.0f, 0.0f,	1
			// 0.0f, 0.0f, 1.0f,	2
			// 1.0f, 1.0f, 0.0f,	3

			// 0.0f, 1.0f, 1.0f,	4
			// 1.0f, 0.0f, 1.0f,	5
			// 0.0f, 0.0f, 0.0f,	6
			// 1.0f, 1.0f, 1.0f		7

			c0[0], c0[1], c0[2],	// 윗면		0, 2, 1 / 1, 2, 3 
			c2[0], c2[1], c2[2],
			c1[0], c1[1], c1[2],
			c1[0], c1[1], c1[2],
			c2[0], c2[1], c2[2],
			c3[0], c3[1], c3[2],

			c0[0], c0[1], c0[2],	// 왼쪽면	0, 4, 2 / 2, 4, 6
			c4[0], c4[1], c4[2],
			c2[0], c2[1], c2[2],
			c2[0], c2[1], c2[2],
			c4[0], c4[1], c4[2],
			c6[0], c6[1], c6[2],
			
			c2[0], c2[1], c2[2],	// 앞면		2, 6, 3 / 3, 6, 7
			c6[0], c6[1], c6[2],
			c3[0], c3[1], c3[2],
			c3[0], c3[1], c3[2],
			c6[0], c6[1], c6[2],
			c7[0], c7[1], c7[2],

			c1[0], c1[1], c1[2],	// 오른쪽면	1, 3, 5 / 5, 3, 7
			c3[0], c3[1], c3[2],
			c5[0], c5[1], c5[2],
			c5[0], c5[1], c5[2],
			c3[0], c3[1], c3[2],
			c7[0], c7[1], c7[2],
			
			c0[0], c0[1], c0[2],	// 뒷면		0, 1, 4 / 1, 5, 4
			c1[0], c1[1], c1[2],
			c4[0], c4[1], c4[2],
			c1[0], c1[1], c1[2],
			c5[0], c5[1], c5[2],
			c4[0], c4[1], c4[2],

			c4[0], c4[1], c4[2],	// 아랫면	4, 5, 6	/ 5, 7, 6
			c5[0], c5[1], c5[2],
			c6[0], c6[1], c6[2],
			c5[0], c5[1], c5[2],
			c7[0], c7[1], c7[2],
			c6[0], c6[1], c6[2],
		};
		_vao = new VAO(vertex, color, 108);
		_indexType = NON_INDEXED;
		break;
	}

	case OBJ_PYRAMID:
	{
		float vertex[]
		{
			// 왼쪽면	4, 0, 2
			_centerPos.x, _centerPos.y + (sqrt(3) * _size) / 2, _centerPos.z,					// 4
			_centerPos.x - _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z - _size,	// 0
			_centerPos.x - _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z + _size,	// 2

			// 앞면		4, 2, 3
			_centerPos.x, _centerPos.y + (sqrt(3) * _size) / 2, _centerPos.z,					// 4
			_centerPos.x - _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z + _size,	// 2
			_centerPos.x + _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z + _size,	// 3

			// 오른쪽면	4, 3, 1
			_centerPos.x, _centerPos.y + (sqrt(3) * _size) / 2, _centerPos.z,					// 4
			_centerPos.x + _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z + _size,	// 3
			_centerPos.x + _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z - _size,	// 1

			// 뒷면		4, 1, 0	
			_centerPos.x, _centerPos.y + (sqrt(3) * _size) / 2, _centerPos.z,					// 4
			_centerPos.x + _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z - _size,	// 1
			_centerPos.x - _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z - _size,	// 0

			// 아랫면	0, 1, 2 / 1, 3, 2
			_centerPos.x - _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z - _size,	// 0
			_centerPos.x + _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z - _size,	// 1
			_centerPos.x - _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z + _size,	// 2

			_centerPos.x + _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z - _size,	// 1
			_centerPos.x + _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z + _size,	// 3
			_centerPos.x - _size, _centerPos.y - (sqrt(3) * _size) / 2, _centerPos.z + _size	// 2

		};

		glm::vec3 c0 = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 c1 = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 c2 = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 c3 = glm::vec3(1.0f, 1.0f, 0.0f);
		glm::vec3 c4 = glm::vec3(0.0f, 1.0f, 1.0f);

		float color[]
		{
			// 왼쪽면	4, 0, 2
			c4[0], c4[1], c4[2],	// 4
			c0[0], c0[1], c0[2],	// 0
			c2[0], c2[1], c2[2],	// 2

			// 앞면		4, 2, 3
			c4[0], c4[1], c4[2],	// 4
			c2[0], c2[1], c2[2],	// 2
			c3[0], c3[1], c3[2],	// 3

			// 오른쪽면	4, 3, 1
			c4[0], c4[1], c4[2],	// 4
			c3[0], c3[1], c3[2],	// 3
			c1[0], c1[1], c1[2],	// 1

			// 뒷면		4, 1, 0	
			c4[0], c4[1], c4[2],	// 4
			c1[0], c1[1], c1[2],	// 1
			c0[0], c0[1], c0[2],	// 0

			// 아랫면	0, 1, 2 / 1, 3, 2
			c0[0], c0[1], c0[2],	// 0
			c1[0], c1[1], c1[2],	// 1
			c2[0], c2[1], c2[2],	// 2

			c1[0], c1[1], c1[2],	// 1
			c3[0], c3[1], c3[2],	// 3
			c2[0], c2[1], c2[2],	// 2
		};
		_vao = new VAO(vertex, color, 54);
		_indexType = NON_INDEXED;
		break;
	}
	}
}

void Objects::CreateQuadricObject(GLenum drawType)
{
	_qObj = gluNewQuadric();
	gluQuadricDrawStyle(_qObj, drawType);
}

void Objects::CreateCubeUsingParams(float left, float top, float right, float bottom, float floorHeight, float ceilingHeight)
{
	float vertex[] =
	{
		left, ceilingHeight, top,
		right, ceilingHeight, top,
		left, ceilingHeight, bottom,
		right, ceilingHeight, bottom,

		left, floorHeight, top,
		right, floorHeight, top,
		left, floorHeight, bottom,
		right, floorHeight, bottom

	};
	float color[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f
	};
	unsigned int element[] =
	{
		0, 2, 1,	// 면 1
		1, 2, 3,
		0, 4, 2,	// 면 2
		2, 4, 6,
		2, 6, 3,	// 면 3
		3, 6, 7,
		1, 3, 5,	// 면 4
		3, 7, 5,
		0, 1, 4,	// 면 5
		1, 5, 4,
		6, 4, 5,	// 면 6
		6, 5, 7
	};
	_vao = new VAO(vertex, color, element, 24, 36);
	_centerPos.x = (left + right) / 2;
	_centerPos.y = (floorHeight + ceilingHeight) / 2;
	_centerPos.z = (top + bottom) / 2;
	_indexType = INDEXED;

}

void Objects::SetQuadricDrawType(GLenum drawType)
{
	_drawType = drawType;
	gluQuadricDrawStyle(_qObj, drawType);
}

void Objects::ChangeColor(RGB rgb)
{
	float* cBuf = &_vao->GetColorBuffer()[0];
	int bufSize = _vao->GetVertexCount();
	
	for (int i = 0; i < bufSize; i += 3)
	{
		cBuf[i] = rgb.Red;
		cBuf[i + 1] = rgb.Green;
		cBuf[i + 2] = rgb.Blue;
	}
	
	_vao->InitVAO(INDEXED);

}

void Objects::Render()
{
	if (this == nullptr)
		return;

	
	if(_qType == NONE)
	{
		glBindVertexArray(_vao->GetVAOHandle());
		if (_indexType == NON_INDEXED)
		{
			glDrawArrays(GL_TRIANGLES, 0, _vao->GetVertexCount());
		}
		else
		{
			glDrawElements(GL_TRIANGLES, _vao->GetElementCount(), GL_UNSIGNED_INT, 0);
		}
	}
	else
	{
		switch (_qType)
		{
		case QOBJ_SPHERE:
		{
			glColor4f(_rgb.Red, _rgb.Green, _rgb.Blue, 1.0f);
			gluSphere(_qObj, _size, 20, 20);
			break;
		}

		case QOBJ_CYLINDER:
			glColor3f(_rgb.Red, _rgb.Green, _rgb.Blue);
			gluCylinder(_qObj, _size, 0.2, 0.5, 20, 8);
			break;

		case QOBJ_CONE:
			glColor3f(_rgb.Red, _rgb.Green, _rgb.Blue);
			gluCylinder(_qObj, _size, 0.0, 0.5, 20, 8);
			break;

		case QOBJ_DISK:
			glColor3f(_rgb.Red, _rgb.Green, _rgb.Blue);
			gluDisk(_qObj, _size, 0.4, 20, 3);
			break;
		}
	}

	glutPostRedisplay();
}




