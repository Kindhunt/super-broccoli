#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		// ID ссылка Шейдерной Программы
		GLuint ID;
		// Конструктор который строит Шейдерную Программу из 2 других шейдеров
		Shader(const char* vertexFile, const char* fragmentFile);

		// Активирует Шейдерную Программу
		void Activate();
		// Удаляет Шейдерную Программу
		void Delete();

		void compileErrors(unsigned int shader, const char* type);
};
#endif