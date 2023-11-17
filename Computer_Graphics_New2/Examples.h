#pragma once

// �ǽ� Ŭ���� �������̽�
class Examples
{
public:
	virtual ~Examples();


protected:
	virtual void drawScene() = 0;
	virtual void Reshape(int w, int h) = 0;

	// �ǽ� ��ü�� �ʱ�ȭ�մϴ�.
	virtual void InitEx() = 0;

	virtual void MouseUpdate() = 0;
	virtual void MotionUpdate() = 0;
	virtual void KeyboardUpdate() = 0;
	virtual void SpecialKeyUpdate() = 0;

	// �ǽ� ��ü ������ ��ҵ��� �� �ѹ� ������Ʈ �մϴ�.

};

