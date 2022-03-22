#include "Model.h"
const unsigned int width = 900;
const unsigned int height = 900;


int main()
{
	// Инициализация GLFW
	glfwInit(); 


	// Говорим GLFW какую версию OpenGL мы используем
	// Здесь мы используем OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Говорим GLFW что мы используем CORE профиль
	// И так это значит что мы используем только современные функции
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Создаём GLFWwindow объект размером 800 на 800 пикселей, называем его "Dream"
	GLFWwindow* window = glfwCreateWindow(width, height, "Dream", NULL, NULL);

	// Проверка на ошибку, если окно не было создано
	if (window == NULL)
	{
		std::cout << "no" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Вводим окно в текущий контекст
	glfwMakeContextCurrent(window);
		
	// Загружаем GLAD который конфигурирует OpenGL
	gladLoadGL();

	// Уточняем (специфицируем) окно просмотра OpenGL в Window
	// В этом случае окно просмотра меняется от x = 0, y = 0 на x = 800, y = 800
	glViewport(0, 0, width, height);
	
	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);

	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	Model model("models/sword/scene.gltf");

	// Основной цикл
	while (!glfwWindowShouldClose(window))
	{
		// Уточняем цвет заднего фона
		glClearColor(0.03f, 0.14f, 0.15f, 1.0f);
		// Очищаем задний буффер и присваиваем ему новый цвет
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Говорим OpenGL какую Шейдерную Программу мы хотим использовать
		

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);

		
		// Меняем задний буффер с передним буффером 
		glfwSwapBuffers(window);
		// Заботимся обо всех GLFW событиях
		glfwPollEvents();
	}

	// Удаляем все объекты которые мы создали
	
	shaderProgram.Delete();
	// Удаляем окно после окончания программы
	glfwDestroyWindow(window);
	// Выключаем GLFW после окончания программы
	glfwTerminate();

	return 0;
}