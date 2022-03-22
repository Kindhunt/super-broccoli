#include "VAO.h"

// Конструктор который генерирует VAO ID
VAO::VAO()
{

	glGenVertexArrays(1, &ID);
}

// Линкует VBO к VAO используя определенный layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{

	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Биндит VAO
void VAO::Bind()
{

	glBindVertexArray(ID);
}

// Анбиндит VAO
void VAO::Unbind()
{

	glBindVertexArray(0);
}

// Удаляет VAO
void VAO::Delete()
{

	glDeleteVertexArrays(1, &ID);
}