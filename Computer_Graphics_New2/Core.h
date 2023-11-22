#pragma once

class Core
{
public:

	static Core& GetInstance();
	
	void InitScreen(int argc, char** argv, int position_x, int position_y, int width, int height, string windowName);
	void InitShader();
	/* drawScene�� Reshape�� ���� ����� ���ε��ϸ� �ݹ��Լ��� ȣ��˴ϴ�.*/
	void BindDrawCallback(void (*funcptr)());
	void BindReshapeCallback(void (*funcptr)(int w, int h));

	/* �Ʒ��� 4���� �Լ��� �� �ݹ��� ����Ϸ��� �Ҷ� ȣ���ϸ� �˴ϴ�.*/
	void UseMouseCallback();
	void UseMotionCallback();
	void UseKeyboardCallback();
	void UseSpecialKeyCallback();

	int GetShaderID() { return shader->GetShaderID(); }
	int GetuShaderID() { return shader->GetuShaderID(); }
	int GetTexShaderID() { return shader->GetTexShaderID(); }

private:
	Core();
	~Core();

private:
	Shaders* shader;
};
