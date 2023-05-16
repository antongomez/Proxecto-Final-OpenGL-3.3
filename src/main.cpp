
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
#include "encabezados/Camara.hpp"
#include "encabezados/Renderizador.hpp"
#include "encabezados/FigurasXeometricas.hpp"
#include "encabezados/Obxecto.hpp"
#include "encabezados/Suelo.hpp"
#include "encabezados/Enemigo.hpp"
#include "encabezados/PersonaxePrincipal.hpp"

#include "encabezados/definicions.h"

// Tamanhos iniciais da venta
const unsigned int Camara::SCR_WIDTH = 800;
const unsigned int Camara::SCR_HEIGHT = 800;

// Obxectos que se encarga de debuxar cubos, cadrados, e figuras mais complexas

// Obxecto que renderiza a escena
Renderizador* renderizador = new Renderizador();

// Lista de enemigos
PersonaxePrincipal* personaxePrincipal;
std::vector<Enemigo*> enemigos;

// So debuxamos os eixos no main. O resto das figuras xeometricas debuxanse nas clases que as utilizan
FigurasXeometricas* fgEixos;

GLuint shaderProgram;

GLFWwindow* crearVenta();
void processInput(GLFWwindow* window);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void xerarInimigos(int numEnemigos, float distmin, float distmax);

int main()
{
	GLFWwindow* window = crearVenta();

	// Xeramos o Shaders
	shaderProgram = setShaders("recursos/shaders/shader.vert", "recursos/shaders/shader.frag");

	// Establecemos o shader que usa a camara
	renderizador->setShaderProgram(shaderProgram);

	// Obten a ubicación das matrices de vista e proxeccion no programa de shader
	GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

	glUseProgram(shaderProgram);

	fgEixos = new FigurasXeometricas(FIGURA_EIXOS);

	// Creamos a instancia do chan
	float limitesx[2] = { -10.0, 10.0 };
	float limitesz[2] = { -10.0, 10.0 };
	Suelo* suelo = new Suelo(0, 0, 2.0f, limitesx, limitesz, shaderProgram, FIGURA_CADRADO);

	// Creamos as instancias dos obxectos
	float escala = 0.5f;
	personaxePrincipal = new PersonaxePrincipal(glm::vec3(0, ALTURA_Y + escala / 2.0f, 0), glm::vec3(escala, escala, escala), shaderProgram, FIGURA_CARGADA, 0);
	renderizador->introducirElementoEscena(personaxePrincipal);

	// Xeramos os enemigos e os obxectos da escena
	xerarInimigos(20, 5, 10);

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

		for (int i = 0; i < enemigos.size(); i++) {
			enemigos[i]->moverEnemigo(tempoTranscurrido);
		}

		personaxePrincipal->moverPersonaxe(tempoTranscurrido);

		renderizador->establecerCamara(CAMARA_XERAL, personaxePrincipal->posicion);

		// Debuxamos os eixos
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
		fgEixos->renderizar();


		// Renderizamos os obxectos
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		suelo->renderizarSuelo();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		renderizador->renderizarEscena();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete fgEixos;

	glfwTerminate();
	return 0;
}

void xerarInimigos(int numEnemigos, float mindist, float maxdist) {
	float escala = 0.4f;

	std::random_device rd;
	std::mt19937 generator(rd());

	// Definir una distribución para generar números reales en un rango
	std::uniform_real_distribution<double> distribucionRadio(mindist, maxdist);
	std::uniform_real_distribution<double> distribucionAngulo(0, 2 * PI);

	for (int i = 0; i < numEnemigos; i++) {
		float radio = (float)distribucionRadio(generator);
		float angulo = (float)distribucionAngulo(generator);

		glm::vec3 posicion(radio * glm::sin(angulo), ALTURA_Y + escala / 2.0f, radio * glm::cos(angulo));
		glm::vec3 escala(0.4f);

		Enemigo* enemigo = new Enemigo(posicion, escala, shaderProgram, FIGURA_CUBO, 1, personaxePrincipal);

		renderizador->introducirElementoEscena(enemigo);
		enemigos.push_back(enemigo);
	}
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


// Implementación de la función de callback para cambiar el tamaño de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (renderizador != NULL) {
		renderizador->reescalarVenta(window, width, height);
	}
}


// Funcion que controla as teclas
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << key << std::endl;

	// Tecla d: xiro do personaxe a dereita
	if (key == 68 && action != GLFW_RELEASE) {
		personaxePrincipal->angulo -= INCREMENTO_XIRO_PERSONAXE;
	}

	// Tecla a: xiro do personaxe a esquerda
	if (key == 65 && action != GLFW_RELEASE) {
		personaxePrincipal->angulo += INCREMENTO_XIRO_PERSONAXE;
	}

	// Tecla w: desprazarse cara diante
	if (key == 87) {

		if (action == GLFW_PRESS) {
			personaxePrincipal->moverse = true;
		}

		if (action == GLFW_RELEASE) {
			personaxePrincipal->moverse = false;
		}
	}

	// Tecla s: desprazarse cara atras
	if (key == 83) {

		if (action == GLFW_PRESS) {
			personaxePrincipal->moverse = true;
		}

		if (action == GLFW_RELEASE) {
			personaxePrincipal->moverse = false;
		}
	}

	// Tecla dereita: xiro da camara en vistaXeral a dereita
	if (key == 262) {
		renderizador->moverCamara(XIRO_CAMARA_DEREITA);
	}

	// Tecla esquerda: xiro da camara en vistaXeral a esquerda
	if (key == 263) {
		renderizador->moverCamara(XIRO_CAMARA_ESQUERDA);
	}

	// Tecla arriba: xiro da camara en vistaXeral na vertical cara arriba
	if (key == 265) {
		renderizador->moverCamara(XIRO_CAMARA_ARRIBA);
	}

	// Tecla abaixo: xiro da camara en vistaXeral na vertical cara abaixo
	if (key == 264) {
		renderizador->moverCamara(XIRO_CAMARA_ABAIXO);
	}

	// Tecla +: achegase a camara en vistaXeral
	if (key == 93 && action != GLFW_RELEASE) {
		renderizador->moverCamara(ACERCAR_CAMARA);
	}

	// Tecla -: afastase a camara en vistaXeral
	if (key == 47 && action != GLFW_RELEASE) {
		renderizador->moverCamara(AFASTAR_CAMARA);
	}


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