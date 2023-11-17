#pragma once

enum OBJ_TYPE_2D
{
	OBJ_POINT = 0,
	OBJ_LINE,
	OBJ_TRIANGLE,
	OBJ_RECTANGLE,
	OBJ_PENTAGON,
};

enum OBJ_TYPE_3D
{
	OBJ_TETRAHEDRON = 0,
	OBJ_CUBE,
	OBJ_PYRAMID,
	OBJ_PLANE_RECT,
	OBJ_PLANE_TRIANGLE
};

enum QOBJ_TYPE	// Quadric Objects
{
	QOBJ_SPHERE = 0,
	QOBJ_CYLINDER,
	QOBJ_CONE,
	QOBJ_DISK,
	NONE
};

enum AXIS
{
	X_AXIS = 0,
	Y_AXIS,
	Z_AXIS
};

class Objects
{
public:
	// 2D���� ������
	Objects(OBJ_TYPE_2D type, Coord pos, float size);
	// 3D���� ������, �ǵ��� �Ʒ� �����ڸ� ���, ���� �ǽ��� ȣȯ�� ������ ���Ž÷� ���ܵ�
	Objects(OBJ_TYPE_3D type, Coord pos, float size);
	// 3D NON-INDEXED ������, INDEXED�ε� ���� �����ϹǷ� �����ϸ� �̰� ���
	Objects(OBJ_TYPE_3D type, Coord pos, float size, VAO_TYPE indexType);
	// Quadric Objects ���� ������
	Objects(QOBJ_TYPE type, Coord pos, float size, GLenum drawType, RGB rgb);

	// ����ü CUBE ���� ������ -> ���鸸 ��������
	// �ٴڸ��� �»��, ���ϴ�, ���̸� �޾Ƽ� ����
	// 3D MAX�� �׸��� ��İ� ����, ũ������ ���鶧 �� ���� ������� �ӽ÷� ���� ������
	Objects(float left, float top, float right, float bottom,float floorHeight, float ceilingHeight);
	
	~Objects();

private:
	void CreateObject2D(OBJ_TYPE_2D type);
	void CreateObject3D(OBJ_TYPE_3D type);
	void CreateNonIndexedObject3D(OBJ_TYPE_3D type);
	void CreateQuadricObject(GLenum drawType);

	void CreateCubeUsingParams(float left, float top, float right, float bottom, float floorHeight, float height);

public:
	// ��ƿ�Լ�
	VAO& GetVAO() { return *_vao; }
	Coord GetCenter() { return _centerPos; }
	void ChangeColor(RGB rgb);	// ���� �ٲٰų� ����, �ܻ����θ� ������
	float GetSize() { return _size; }

	// ������
	void Render();
	
	void SetQuadricDrawType(GLenum drawType);


	// Quadric Object���� Ȯ���ϴ� flag ��ȯ
	bool isQuadric()
	{
		if (_qType == NONE)
			return false;
		else
			return true;
	}

private:
	VAO* _vao = nullptr;
	Coord _centerPos = { 0,0 };
	float _size = 0.0f;

	// Quadric Object�� ���� ����
	QOBJ_TYPE _qType = NONE;
	GLUquadricObj* _qObj = nullptr;
	GLenum _drawType = GL_NONE;
	RGB _rgb = { 0.0f, 0.0f, 0.0f };



	VAO_TYPE _indexType = NON_INDEXED;

};

