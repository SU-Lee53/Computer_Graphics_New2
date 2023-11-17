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
	// 2D전용 생성자
	Objects(OBJ_TYPE_2D type, Coord pos, float size);
	// 3D전용 생성자, 되도록 아래 생성자를 사용, 이전 실습과 호환성 문제로 레거시로 남겨둠
	Objects(OBJ_TYPE_3D type, Coord pos, float size);
	// 3D NON-INDEXED 생성자, INDEXED로도 생성 가능하므로 가능하면 이걸 사용
	Objects(OBJ_TYPE_3D type, Coord pos, float size, VAO_TYPE indexType);
	// Quadric Objects 전용 생성자
	Objects(QOBJ_TYPE type, Coord pos, float size, GLenum drawType, RGB rgb);

	// 육면체 CUBE 전용 생성자 -> 육면만 생성가능
	// 바닥면의 좌상단, 우하단, 높이를 받아서 생성
	// 3D MAX의 그리기 방식과 유사, 크레인을 만들때 더 쉽게 만들려고 임시로 만든 생성자
	Objects(float left, float top, float right, float bottom,float floorHeight, float ceilingHeight);
	
	~Objects();

private:
	void CreateObject2D(OBJ_TYPE_2D type);
	void CreateObject3D(OBJ_TYPE_3D type);
	void CreateNonIndexedObject3D(OBJ_TYPE_3D type);
	void CreateQuadricObject(GLenum drawType);

	void CreateCubeUsingParams(float left, float top, float right, float bottom, float floorHeight, float height);

public:
	// 유틸함수
	VAO& GetVAO() { return *_vao; }
	Coord GetCenter() { return _centerPos; }
	void ChangeColor(RGB rgb);	// 색을 바꾸거나 지정, 단색으로만 가능함
	float GetSize() { return _size; }

	// 렌더링
	void Render();
	
	void SetQuadricDrawType(GLenum drawType);


	// Quadric Object인지 확인하는 flag 반환
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

	// Quadric Object를 위한 변수
	QOBJ_TYPE _qType = NONE;
	GLUquadricObj* _qObj = nullptr;
	GLenum _drawType = GL_NONE;
	RGB _rgb = { 0.0f, 0.0f, 0.0f };



	VAO_TYPE _indexType = NON_INDEXED;

};

