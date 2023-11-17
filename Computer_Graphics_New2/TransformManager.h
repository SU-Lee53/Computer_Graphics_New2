#pragma once

class TransformManager
{
public:
	static TransformManager& GetInstance()
	{
		static TransformManager instance;
		return instance;
	}
	
	glm::mat4 GetTranslateMatrix(glm::vec3 move);

	// x,y,z,���� ȸ�������� �̿��Ҷ� ����մϴ�.
	glm::mat4 GetRotateMatrix(float degree, AXIS axis);

	// ������ ȸ������ �̿��Ҷ� ����մϴ�.
	glm::mat4 GetRotateMatrix(float degree, glm::vec3 axis);

	glm::mat4 GetScaleMatrix(glm::vec3 scale);

	void Bind(glm::mat4 matrix, unsigned int shaderID);

private:
	TransformManager();
	~TransformManager();

};

