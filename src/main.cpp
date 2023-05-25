
#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <random>
#include <vector>

#include "encabezados/lecturaShader_0_9.h"
#include "encabezados/Camara.hpp";
#include "encabezados/Partida.hpp";

#include "encabezados/definicions.h"

// Tamanhos iniciais da venta
const unsigned int Camara::SCR_WIDTH = 800;
const unsigned int Camara::SCR_HEIGHT = 800;

// Obxecto que leva a cabo a loxica do xogo e intercambia os mundos
Partida* partida = NULL;

GLFWwindow* crearVenta();
void processInput(GLFWwindow* window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	GLFWwindow* window = crearVenta();

	// Xeramos os Shaders
	GLuint shaderProgram = setShaders("recursos/shaders/shader.vert", "recursos/shaders/shader.frag");
	GLuint shaderProgramTex = setShaders("recursos/shaders/shaderTex.vert", "recursos/shaders/shaderTex.frag");

	partida = new Partida(shaderProgram, shaderProgramTex);

	// Obten a ubicación das matrices de vista e proxeccion no programa de shader
	GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	// Variables para o control do tempo
	double tempoAnterior = 0;

	// Lazo da venta mentres non se peche
	while (!glfwWindowShouldClose(window))
	{

		// Xestion do tempo
		double tempoActual = glfwGetTime();
		double tempoTranscurrido = tempoActual - tempoAnterior;
		tempoAnterior = tempoActual;

		processInput(window);

		// Limpamos o buffer de profundidade e cor en cada iteracion
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		partida->moverObxectos(tempoTranscurrido);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


// Implementación de la función de callback para cambiar el tamaño de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (partida != NULL) {
		partida->reescalarVenta(window, width, height);
	}
}

// Funcion que controla as teclas
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << key << std::endl;

	partida->eventoTeclado(key, action);
}


// Funcion de inicializacion de valores
void openGLInit() {
	glClearDepth(1.0f); // Valor z-buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // valor limpeza buffer cor
	glEnable(GL_DEPTH_TEST); // z-buffer
	glEnable(GL_CULL_FACE); // ocultacion caras back
	glCullFace(GL_BACK);
}

// Funcion que crea a venta e establece as funcions para detectar as pulsacions de teclado 
GLFWwindow* crearVenta() {
	// Inicializacion
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creamos a venta
	GLFWwindow* window = glfwCreateWindow(Camara::SCR_WIDTH, Camara::SCR_HEIGHT, "EndGame", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Asignacion do contexto de OpenGL a venta
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Establecemento da funcion callback para cambiar o tamanho da venta
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Funcion que rexistra as pulsacions de teclado
	glfwSetKeyCallback(window, keyCallback);

	openGLInit();

	return window;
}