#pragma once

struct MouseState
{
	int button;
	int state;
	Coord pos;
};

struct KeyboardState
{
	unsigned char key;
	Coord pos;
};

struct SpecialState
{
	int key;
	Coord pos;
};

enum INPUT_TYPE
{
	MOUSE = 0,
	MOTION,
	KEYBOARD,
	SPECIAL
};

// InputManager�� �ǽ� ��ü�� ���ӵ��� �ʰ� �̱������� �۵���
// ���� ������: �̱��� ��ü ���� �����Լ� -> �����ʴ�
class InputManager
{
public:

	static InputManager& GetInstance()
	{
		static InputManager instance;
		return instance;
	}

	// �ݹ鿡���� ���ۿ� �Է¸� �־��ְ� �ǽ���ü���� ���۸� ������ �ϳ��� ó���Ѵ�.
	void (*MouseFunc())(int, int, int, int) { return MouseInput; }
	void (*MotionFunc())(int, int) { return MotionInput; }
	void (*KeyboardFunc())(unsigned char, int, int) { return KeyboardInput; }
	void (*SpecialKeyFunc())(int, int, int) { return SpecialKeyInput; }

	MouseState* DequeueMouseBuf();
	Coord* DequeueMotionBuf();
	KeyboardState* DequeueKeyboardBuf();
	SpecialState* DequeueSpecialKeyBuf();

private:
	InputManager();
	~InputManager();
	static void MouseInput(int button, int state, int x, int y);
	static void MotionInput(int x, int y);
	static void KeyboardInput(unsigned char key, int x, int y);
	static void SpecialKeyInput(int key, int x, int y);

	queue<MouseState*>& GetMouseBuf() { return mouseBuf; }
	queue<Coord*>& GetMotionBuf() { return motionBuf; }
	queue<KeyboardState*>& GetKeyboardBuf() { return keyboardBuf; }
	queue<SpecialState*>& GetSpecialKeyBuf() { return specialKeyBuf; }

private:

	// �Է� ����
	queue<MouseState*> mouseBuf;
	queue<KeyboardState*> keyboardBuf;
	queue<Coord*> motionBuf;
	queue<SpecialState*> specialKeyBuf;
};

