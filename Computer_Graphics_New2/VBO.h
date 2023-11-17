#pragma once

const int MAX_VERTEX_COUNT = 1024;

class VBO
{
public:
	VBO();
	~VBO();

	// VBO객체 내부 버퍼에 생성된 도형의 버퍼를 집어넣습니다.
	void PushToVertexBuffer(float* buf, int bufSize);
	void PushToColorBuffer(float* buf, int bufSize);

	// VBO 객체 내부 eBuf(element)에 인덱스를 넣습니다.
	void PushToElementBuffer(unsigned int* buf, int ebufSize);

	// VBO 객체 내부 nBuf(normal)에 노말벡터를 넣습니다.
	void PushToNormalBuffer(float* buf, int bufSize);

	// VBO 객체 내부에 텍스쳐 UV를 넣습니다...?
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

	// 아 벡터로 바꾸고십따ㅇㅇ
	vector<float> __vBuf;
	vector<float> __cBuf;
	vector<float> __nBuf;
	vector<float> __tBuf;
	vector<unsigned int> __eBuf;


};

