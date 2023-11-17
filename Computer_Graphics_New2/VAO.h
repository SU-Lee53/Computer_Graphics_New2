#pragma once

enum VAO_TYPE
{
	NON_INDEXED = 0,
	INDEXED,
	NORMAL_AND_TEXTURE
};


class VAO
{
public:
	// ����, ���� ���۸� �޴� ������
	VAO(float* vertex, float* color, int bufSize);
	// ����, ����, �ε��� ���۸� ��� �޴� ������
	VAO(float* vertex, float* color, unsigned int* element, int vBufSize, int eBufSize);
	// ����, ����, �ε���, �븻���� �޴� ������....
	VAO(float* vertex, float* normal, float* color, unsigned int* element, int vBufSize, int eBufSize);
	~VAO();

	// VAO_TYPE: NON_INDEXED or INDEXED
	void InitVAO(VAO_TYPE type);

	void ChangeElementBuffer(unsigned int* element, int eBufSize);

	unsigned int GetVAOHandle() { return h_VAO; }
	int GetVertexCount() { return _vBufSize; }
	int GetElementCount() { return _eBufSize; }
	vector<float>& GetVertexBuffer() { return _vbo.GetVertexBuf(); }
	vector<float>& GetColorBuffer() { return _vbo.GetColorBuf(); }
	vector<float>& GetTextureBuffer() { return _vbo.GetTextureBuf(); }
	vector<float>& GetNormalBuffer() { return _vbo.GetNormalBuf(); }
	vector<unsigned int>& GetElementBuffer() { return _vbo.GetElementBuf(); }
	VAO_TYPE GetVaoType() { return _vaoType; }

private:

	unsigned int h_VAO = 0;		// VAO �ڵ�
	VBO _vbo;				
	int _vBufSize;	// == cBufSize
	int _eBufSize;
	VAO_TYPE _vaoType;

};

