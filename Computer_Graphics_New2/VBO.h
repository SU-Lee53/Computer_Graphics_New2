#pragma once

const int MAX_VERTEX_COUNT = 1024;

class VBO
{
public:
	VBO();
	~VBO();

	// VBO��ü ���� ���ۿ� ������ ������ ���۸� ����ֽ��ϴ�.
	void PushToVertexBuffer(float* buf, int bufSize);
	void PushToColorBuffer(float* buf, int bufSize);

	// VBO ��ü ���� eBuf(element)�� �ε����� �ֽ��ϴ�.
	void PushToElementBuffer(unsigned int* buf, int ebufSize);

	// VBO ��ü ���� nBuf(normal)�� �븻���͸� �ֽ��ϴ�.
	void PushToNormalBuffer(float* buf, int bufSize);

	// VBO ��ü ���ο� �ؽ��� UV�� �ֽ��ϴ�...?
	void PushToTextureBuffer(float* buf, int bufSize);

	unsigned int* GetVertexHandle() { return &vBufHandle; }
	unsigned int* GetColorHandle() { return &cBufHandle; }
	unsigned int* GetNormalHandle() { return &nBufHandle; }
	unsigned int* GetTextureHandle() { return &tBufHandle; }
	unsigned int* GetElementHandle() { return &eBufHandle; }
	
	vector<float>& GetVertexBuf() { return __vBuf; }
	vector<float>& GetColorBuf() { return __cBuf; }
	vector<float>& GetNormalBuf() { return __nBuf; }
	vector<float>& GetTextureBuf() { return __tBuf; }
	vector<unsigned int>& GetElementBuf() { return __eBuf; }

private:
	unsigned int vBufHandle = 0;
	unsigned int cBufHandle = 0;
	unsigned int nBufHandle = 0;
	unsigned int tBufHandle = 0;
	unsigned int eBufHandle = 0;
	float vBuf[MAX_VERTEX_COUNT];
	float cBuf[MAX_VERTEX_COUNT];
	float nBuf[MAX_VERTEX_COUNT];
	float tBuf[MAX_VERTEX_COUNT];
	unsigned int eBuf[MAX_VERTEX_COUNT *3];

	// �� ���ͷ� �ٲٰ�ʵ�����
	vector<float> __vBuf;
	vector<float> __cBuf;
	vector<float> __nBuf;
	vector<float> __tBuf;
	vector<unsigned int> __eBuf;


};

