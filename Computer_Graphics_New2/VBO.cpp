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
		vector<float>().swap(__tBuf);
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

	__vBuf.resize(0);
	copy(buf, buf + bufSize, back_inserter(__vBuf));
}

void VBO::PushToColorBuffer(float* buf, int bufSize)
{
	//	memset(this->cBuf, 0.0f, sizeof(float) * 256);
	//	memcpy(this->cBuf, buf, sizeof(float) * bufSize);

	__cBuf.resize(0);
	copy(buf, buf + bufSize, back_inserter(__cBuf));
}

void VBO::PushToElementBuffer(unsigned int* eBuf, int ebufSize)
{
	//	memset(this->eBuf, 0, sizeof(unsigned int) * 256);
	//	memcpy(this->eBuf, eBuf, sizeof(unsigned int) * ebufSize);

	__eBuf.resize(0);
	copy(eBuf, eBuf + ebufSize, back_inserter(__eBuf));
}

void VBO::PushToNormalBuffer(float* buf, int bufSize)
{
	__nBuf.resize(0);
	copy(buf, buf + bufSize, back_inserter(__nBuf));
}

void VBO::PushToTextureBuffer(float* buf, int bufSize)
{
	__tBuf.resize(0);
	copy(buf, buf + bufSize, back_inserter(__tBuf));
}
