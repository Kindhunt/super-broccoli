#include "shaderClass.h"

// Читаем текстовый файл и выводит строку со всем содержиммым текстового файла
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Конструктор который строит Шейдерную Программу из 2 других шейдеров
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Читает vertexFile и fragmentFile и хранит в виде строки
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Конвертирует строки источника шейдера в сивольные массивы
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Создаём Вершинный Шейдерный Объект и берём ссылку
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Прикрепляем источник Вершинного Шейдера к Вершинному Шейдерному Объекту
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Компилируем Вершинный Шейдер в машинный код
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	// Создаём Фрагментный Шейдерный Объект и берём ссылку
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Прикрепляем источник Фрагментного Шейдера к Фрагментному Шейдерному Объекту
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Компилируем Фрагментный Шейдер в машинный код
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	// Создаём Шейдерную Программу
	ID = glCreateProgram();
	// Крепим к ней Вершинный Шейдерный Объект
	glAttachShader(ID, vertexShader);
	// Крепим к ней Фрагментный Шейдерный Объект
	glAttachShader(ID, fragmentShader);
	// Линкуем шейдеры вместе в Шейдерную Программу
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	// Удаляем Вершинный Шейдерный Объект
	glDeleteShader(vertexShader);
	// Удаляем Фрагментный Шейдерный Объект 
	glDeleteShader(fragmentShader);
}

// Активирует Шейдерную Программу
void Shader::Activate()
{
	glUseProgram(ID);
}

// Удаляет Шейдерную Программу
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;

		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if(hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
}