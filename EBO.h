#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
	public:
		// ID ������ ��������� ��������� �������
		GLuint ID;
		// ����������� ���������� �������� ��������� ������� � ���������� �� � indices
		EBO(std::vector<GLuint>& indices);

		// ������ EBO
		void Bind();
		// �������� EBO
		void Unbind();
		// ������� EBO
		void Delete();
};

#endif