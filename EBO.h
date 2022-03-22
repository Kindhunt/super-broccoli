#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
	public:
		// ID ссылка Элементов Буферного Объекта
		GLuint ID;
		// Конструктор генерирует Элементы Буферного Объекта и подключает их к indices
		EBO(std::vector<GLuint>& indices);

		// Биндит EBO
		void Bind();
		// Анбиндит EBO
		void Unbind();
		// Удаляет EBO
		void Delete();
};

#endif