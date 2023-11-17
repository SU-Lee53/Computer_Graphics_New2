#pragma once
class Renderer
{
	static Renderer& GetInstance()
	{
		static Renderer instance;
		return instance;
	}

	void Render(VAO* vao);

};

