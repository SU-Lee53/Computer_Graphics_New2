#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::MouseInput(int button, int state, int x, int y)
{
	Coord pos = { x, y };
	pos = AdjustMouseCoordinate(pos);
	MouseState* s = new MouseState{ button, state, pos };
	InputManager::GetInstance().GetMouseBuf().push(s);
}

void InputManager::MotionInput(int x, int y)
{
	Coord pos = AdjustMouseCoordinate({ static_cast<float>(x), static_cast<float>(y) });
	Coord* s = new Coord{ pos.x, pos.y };
	InputManager::GetInstance().GetMotionBuf().push(s);
}

void InputManager::KeyboardInput(unsigned char key, int x, int y)
{
	Coord pos = { x, y };
	pos = AdjustMouseCoordinate(pos);
	KeyboardState* s = new KeyboardState{ key, pos };
	InputManager::GetInstance().GetKeyboardBuf().push(s);
}

void InputManager::SpecialKeyInput(int key, int x, int y)
{
	Coord pos = { x, y };
	pos = AdjustMouseCoordinate(pos);
	SpecialState* s = new SpecialState{ key, pos };
	InputManager::GetInstance().GetSpecialKeyBuf().push(s);
}

MouseState* InputManager::DequeueMouseBuf()
{
	if (mouseBuf.empty())
	{
		return nullptr;
	}
	MouseState* temp = mouseBuf.front();

	// ��ȯ�� ���� ���� �Ҵ�. �ǽ���ü���� ����� �ݵ�� delete �Ұ�
	MouseState* ret = new MouseState{ temp->button, temp->state, temp->pos };
	mouseBuf.pop();
	return ret;
}

Coord* InputManager::DequeueMotionBuf()
{
	if (motionBuf.empty())
	{
		return nullptr;
	}

	Coord* temp = motionBuf.front();

	// ��ȯ�� ���� ���� �Ҵ�. �ǽ���ü���� ����� �ݵ�� delete �Ұ�
	Coord* ret = new Coord{ temp->x, temp->y, temp->z };
	motionBuf.pop();
	return ret;
}

KeyboardState* InputManager::DequeueKeyboardBuf()
{
	if (keyboardBuf.empty())
	{
		return nullptr;
	}

	KeyboardState* temp = keyboardBuf.front();
	KeyboardState* ret = new KeyboardState{ temp->key, temp->pos };
	keyboardBuf.pop();
	return ret;
}

SpecialState* InputManager::DequeueSpecialKeyBuf()
{
	if (specialKeyBuf.empty())
	{
		return nullptr;
	}

	SpecialState* temp = specialKeyBuf.front();
	SpecialState* ret = new SpecialState{ temp->key, temp->pos };
	specialKeyBuf.pop();
	return ret;
}
