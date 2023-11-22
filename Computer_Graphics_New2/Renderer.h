#pragma once
class Renderer
{
public:

	static Renderer& GetInstance()
	{
		static Renderer instance;
		return instance;
	}

	void RenderModel(VAO* vao);

private:
	Renderer();
	~Renderer();

};

