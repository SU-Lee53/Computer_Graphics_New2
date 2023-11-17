#include "pch.h"
#include "VBO.h"

VBO::VBO()
{	
}

VBO::~VBO()
{
	glDeleteBuffers(1, &this->vBufHandle);
	glDeleteBuffers(1, &this->cBufHandle);
	glDeleteBuffers(1, &this->eBufHandle);

	for (int i = 0; i < __vBuf.size(); i++)
	{
		vector<float>().swap(__vBuf);
		vector<float>().swap(__cBuf);
		vector<float>().swap(__nBuf);
	}

	for (int i = 0; i < __eBuf.size(); i++)
	{
		vector<unsigned int>().swap(__eBuf);
	}
}

void VBO::PushToVertexBuffer(float* buf, int bufSize)
{
	//	memset(this->vBuf, 0.0f, sizeof(float) * 256);
	//	memcpy(this->vBuf, buf, sizeof(float) * bufSize);

	__vBuf.reserve(bufSize);
	copy(buf, buf + bufSize, __vBuf.end());
}

void VBO::PushToColorBuffer(float* buf, int bufSize)
{
	//	memset(this->cBuf, 0.0f, sizeof(float) * 256);
	//	memcpy(this->cBuf, buf, sizeof(float) * bufSize);

	__cBuf.reserve(bufSize);
	copy(buf, buf + bufSize, __cBuf.end());
}

void VBO::PushToElementBuffer(unsigned int* eBuf, int ebufSize)
{
	//	memset(this->eBuf, 0, sizeof(unsigned int) * 256);
	//	memcpy(this->eBuf, eBuf, sizeof(unsigned int) * ebufSize);

	__eBuf.reserve(ebufSize);
	copy(eBuf, eBuf + ebufSize, __eBuf.end());
}

void VBO::PushToNormalBuffer(float* buf, int bufSize)
{
	__nBuf.reserve(bufSize);
	copy(buf, buf + bufSize, __nBuf.end());
}

void VBO::PushToTextureBuffer(float* buf, int bufSize)
{
	__nBuf.reserve(bufSize);
	copy(buf, buf + bufSize, __nBuf.end());
}
