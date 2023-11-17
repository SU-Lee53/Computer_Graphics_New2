#pragma once

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

	unsigned int* GetVertexHandle() { return &vBufHandle; }
	unsigned int* GetColorHandle() { return &cBufHandle; }
	unsigned int* GetElementHandle() { return &eBufHandle; }
	float* GetVertexBuf() { return vBuf; }
	float* GetColorBuf() { return cBuf; }
	unsigned int* GetElementBuf() { return eBuf; }

private:
	unsigned int vBufHandle = 0;
	unsigned int cBufHandle = 0;
	unsigned int eBufHandle = 0;
	float vBuf[256];
	float cBuf[256];
	unsigned int eBuf[256];
};

