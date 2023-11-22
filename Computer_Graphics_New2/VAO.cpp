#include "pch.h"
#include "VAO.h"



VAO::VAO(float* vertex, float* color, int bufSize) : _vBufSize(bufSize), _eBufSize(0), _vaoType(NON_INDEXED)
{
	this->_vbo.PushToVertexBuffer(vertex, _vBufSize);
	this->_vbo.PushToColorBuffer(color, _vBufSize);
	InitVAO(NON_INDEXED);
}

VAO::VAO(float* vertex, float* color, unsigned int* element, int v_bufSize, int e_bufSize) : _vBufSize(v_bufSize), _eBufSize(e_bufSize), _vaoType(INDEXED)
{
	this->_vbo.PushToVertexBuffer(vertex, _vBufSize);
	this->_vbo.PushToColorBuffer(color, _vBufSize); 
	this->_vbo.PushToElementBuffer(element, _eBufSize);
	InitVAO(INDEXED);
}

VAO::VAO(float* vertex, float* normal, float* textureUV, unsigned int* element, int vBufSize, int eBufSize, int tBufSize)
	:_vBufSize(vBufSize), _eBufSize(eBufSize), _tBufSize(tBufSize), _vaoType(NORMAL_AND_TEXTURE)
{
	this->_vbo.PushToVertexBuffer(vertex, _vBufSize);
	this->_vbo.PushToNormalBuffer(normal, _vBufSize);
	this->_vbo.PushToTextureBuffer(textureUV, tBufSize);
	this->_vbo.PushToElementBuffer(element, _eBufSize);
	InitVAO(NORMAL_AND_TEXTURE);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &this->h_VAO);
}

void VAO::ChangeElementBuffer(unsigned int* element, int eBufSize)
{
	_vbo.PushToElementBuffer(element, eBufSize);
	_eBufSize = eBufSize;
	InitVAO(INDEXED);
}

void VAO::InitVAO(VAO_TYPE type)	// elementMode�� true�� EBO�� ����ϹǷ� ���� 3�� ������
{
	bool GenBufs = false;	// vbo�� �������� ������ �����ϴ� �÷���

	if (!h_VAO)
	{
		glGenVertexArrays(1, &h_VAO);
		GenBufs = true;
	}

	glBindVertexArray(h_VAO);

	if(type != NORMAL_AND_TEXTURE)
	{

		if (GenBufs == true)
		{
			glGenBuffers(1, _vbo.GetVertexHandle());
			glGenBuffers(1, _vbo.GetColorHandle());
			if (type == INDEXED)
				glGenBuffers(1, _vbo.GetElementHandle());
		}


		glBindBuffer(GL_ARRAY_BUFFER, *_vbo.GetVertexHandle());
		glBufferData(GL_ARRAY_BUFFER, _vBufSize * sizeof(float), &_vbo.GetVertexBuf()[0], GL_DYNAMIC_DRAW);
		if (type == INDEXED)	// element ���� ���ÿ��� vbo �ϳ� �� ���
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *_vbo.GetElementHandle());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, _eBufSize * sizeof(unsigned int), &_vbo.GetElementBuf()[0], GL_DYNAMIC_DRAW);
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, *_vbo.GetColorHandle());
		glBufferData(GL_ARRAY_BUFFER, _vBufSize * sizeof(float), &_vbo.GetColorBuf()[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);

	}
	else
	{
		if (GenBufs == true)
		{
			glGenBuffers(1, _vbo.GetVertexHandle());
			glGenBuffers(1, _vbo.GetNormalHandle());
			glGenBuffers(1, _vbo.GetTextureHandle());
			glGenBuffers(1, _vbo.GetElementHandle());
		}

		// ������ �ε���
		glBindBuffer(GL_ARRAY_BUFFER, *_vbo.GetVertexHandle());
		glBufferData(GL_ARRAY_BUFFER, _vBufSize * sizeof(float), &_vbo.GetVertexBuf()[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *_vbo.GetElementHandle());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _eBufSize * sizeof(unsigned int), &_vbo.GetElementBuf()[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);

		// �븻
		glBindBuffer(GL_ARRAY_BUFFER, *_vbo.GetNormalHandle());
		glBufferData(GL_ARRAY_BUFFER, _vBufSize * sizeof(float), &_vbo.GetNormalBuf()[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(1);

		// �ؽ��� ��ǥ
		glBindBuffer(GL_ARRAY_BUFFER, *_vbo.GetTextureHandle());
		glBufferData(GL_ARRAY_BUFFER, _tBufSize * sizeof(float), &_vbo.GetTextureBuf()[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2, 0);
		glEnableVertexAttribArray(2);



	}

}


