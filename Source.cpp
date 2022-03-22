#include "Model.h"
const unsigned int width = 900;
const unsigned int height = 900;


int main()
{
	// ������������� GLFW
	glfwInit(); 


	// ������� GLFW ����� ������ OpenGL �� ����������
	// ����� �� ���������� OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// ������� GLFW ��� �� ���������� CORE �������
	// � ��� ��� ������ ��� �� ���������� ������ ����������� �������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// ������ GLFWwindow ������ �������� 800 �� 800 ��������, �������� ��� "Dream"
	GLFWwindow* window = glfwCreateWindow(width, height, "Dream", NULL, NULL);

	// �������� �� ������, ���� ���� �� ���� �������
	if (window == NULL)
	{
		std::cout << "no" << std::endl;
		glfwTerminate();
		return -1;
	}

	// ������ ���� � ������� ��������
	glfwMakeContextCurrent(window);
		
	// ��������� GLAD ������� ������������� OpenGL
	gladLoadGL();

	// �������� (�������������) ���� ��������� OpenGL � Window
	// � ���� ������ ���� ��������� �������� �� x = 0, y = 0 �� x = 800, y = 800
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

	// �������� ����
	while (!glfwWindowShouldClose(window))
	{
		// �������� ���� ������� ����
		glClearColor(0.03f, 0.14f, 0.15f, 1.0f);
		// ������� ������ ������ � ����������� ��� ����� ����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// ������� OpenGL ����� ��������� ��������� �� ����� ������������
		

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);

		
		// ������ ������ ������ � �������� �������� 
		glfwSwapBuffers(window);
		// ��������� ��� ���� GLFW ��������
		glfwPollEvents();
	}

	// ������� ��� ������� ������� �� �������
	
	shaderProgram.Delete();
	// ������� ���� ����� ��������� ���������
	glfwDestroyWindow(window);
	// ��������� GLFW ����� ��������� ���������
	glfwTerminate();

	return 0;
}