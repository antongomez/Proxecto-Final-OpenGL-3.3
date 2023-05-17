#include "encabezados/Mundo.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <iostream>

Mundo::Mundo(PersonaxePrincipal* personaxePrincipal, GLuint shaderProgram,
	float alturaMundo, float* limitesx, float* limitesz, 
	int numElementosDecorativos, int nivelMundo) 
{

	this->personaxePrincipal = personaxePrincipal;
	this->shaderProgram = shaderProgram;

	xerarSuelo(alturaMundo, limitesx, limitesz);
	xerarElementosDecorativos(numElementosDecorativos);
	xerarInimigos(nivelMundo);
}

void Mundo::iniciarMundo(){
	this->camara = new Camara(20.0f, PI / 2.0f, (float)PI / 4.0f, shaderProgram);

	// colocamos ao personaxe principal SOBRE o chan no centro do mesmo
	personaxePrincipal->posicion = glm::vec3(suelo->posicion.x, suelo->posicion.y + personaxePrincipal->escalado.y / 2.0f, suelo->posicion.z);
}

void Mundo::xerarSuelo(float alturaMundo, float* limitesx, float* limitesz) {
	this->suelo = new Suelo(glm::vec3(0, alturaMundo, 0), ESCALA_SUELO, limitesx, limitesz, shaderProgram, FIGURA_CADRADO);
}

void Mundo::xerarElementosDecorativos(int numElementosDecorativos) {
	for (int i = 0; i < numElementosDecorativos; i++) {
		// Crear unha pila de arbores e rochas
	}
}

void Mundo::xerarInimigos(int nivelInimigos) {
	int numEnemigos = nivelInimigos * 10;

	std::random_device rd;
	std::mt19937 generator(rd());

	// Definir una distribución para generar números reales en un rango
	std::uniform_real_distribution<double> distribucionRadio(5, suelo->limitesz[1]);
	std::uniform_real_distribution<double> distribucionAngulo(0, 2 * PI);

	float escala = 0.4f;	

	for (int i = 0; i < numEnemigos; i++) {
		float radio = (float)distribucionRadio(generator);
		float angulo = (float)distribucionAngulo(generator);

		glm::vec3 posicion(radio * glm::sin(angulo), suelo->posicion.y + escala / 2.0f, radio * glm::cos(angulo));
		glm::vec3 escala(0.4f);

		Enemigo* enemigo = new Enemigo(posicion, escala, shaderProgram, FIGURA_CUBO, 1, personaxePrincipal);

		inimigos.push_back(enemigo);
	}
}

void Mundo::establecerCamara(int tipoCamara, glm::vec3 target) {
	switch (tipoCamara) {
	case CAMARA_XERAL:
		// Colocamos a camara
		camara->vistaXeral(target);
		break;
	case CAMARA_TERCEIRA_PERSOA:
		break;
	}

	// Actualizamos a matriz de proxeccion
	camara->actualizarMatrizProxeccion();
}

void Mundo::moverObxectos(float tempoTranscurrido) {
	personaxePrincipal->moverPersonaxe(tempoTranscurrido);
	for (int i = 0; i < inimigos.size(); i++) {
		inimigos[i]->moverEnemigo(tempoTranscurrido);
	}
}

void Mundo::renderizarEscena() {
	// Cor da luz que ilumina os obxectos
	glm::vec3 corLuz(1.0f, 1.0f, 1.0f);
	glm::vec3 posLuz(0.0f, 30.0f, 0.0f);

	glm::vec3 dirLight_direccion(2, 0, -1);
	glm::vec3 dirLight_ambiente(0.2f, 0.2f, 0.2f);
	glm::vec3 dirLight_difusa(0.5f, 0.5f, 0.5f);
	glm::vec3 dirLight_espec(1.0f, 1.0f, 1.0f);

	// Establecemos a posicion da camara 
	unsigned int viewPos = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3fv(viewPos, 1, glm::value_ptr(camara->posicionCamara));
	// Establecemos a luz direccional
	unsigned int dirLight_direction = glGetUniformLocation(shaderProgram, "dirLight.direction");
	glUniform3fv(dirLight_direction, 1, glm::value_ptr(dirLight_direccion));
	unsigned int dirLight_ambient = glGetUniformLocation(shaderProgram, "dirLight.ambient");
	glUniform3fv(dirLight_ambient, 1, glm::value_ptr(dirLight_ambiente));
	unsigned int dirLight_diffuse = glGetUniformLocation(shaderProgram, "dirLight.diffuse");
	glUniform3fv(dirLight_diffuse, 1, glm::value_ptr(dirLight_difusa));
	unsigned int dirLight_especular = glGetUniformLocation(shaderProgram, "dirLight.especular");
	glUniform3fv(dirLight_especular, 1, glm::value_ptr(dirLight_espec));

	establecerCamara(CAMARA_XERAL, personaxePrincipal->posicion);

	std::cout << suelo->posicion.x << " " << suelo->posicion.y << " " << suelo->posicion.z << "\n";

	// Renderizamos os obxectos
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	suelo->renderizarSuelo();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	personaxePrincipal->renderizarObxecto();

	for (int i = 0; i < elementosDecorativos.size(); i++) {
		elementosDecorativos[i]->renderizarObxecto();
	}

	for (int i = 0; i < inimigos.size();i++) {
		inimigos[i]->renderizarObxecto();
	}
	
}

// Implementación de la función de callback para cambiar el tamaño de la ventana
void Mundo::reescalarVenta(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camara->width = width;
	camara->height = height;
	camara->actualizarMatrizProxeccion();
}

// Funcion que xestiona os eventos de teclado. Deste xeito cada mundo poderia cambiar, por exemplo, a velocidade de movemento do personaxe
void Mundo::eventoTeclado(int tecla, int accion) {
	// Tecla d: xiro do personaxe a dereita
	if (tecla == 68 && accion != GLFW_RELEASE) {
		personaxePrincipal->angulo -= INCREMENTO_XIRO_PERSONAXE;
	}

	// Tecla a: xiro do personaxe a esquerda
	if (tecla == 65 && accion != GLFW_RELEASE) {
		personaxePrincipal->angulo += INCREMENTO_XIRO_PERSONAXE;
	}

	// Tecla w: desprazarse cara diante
	if (tecla == 87) {

		if (accion == GLFW_PRESS) {
			personaxePrincipal->moverse = true;
		}

		if (accion == GLFW_RELEASE) {
			personaxePrincipal->moverse = false;
		}
	}

	// Tecla s: desprazarse cara atras
	if (tecla == 83) {

		if (accion == GLFW_PRESS) {
			personaxePrincipal->moverse = true;
		}

		if (accion == GLFW_RELEASE) {
			personaxePrincipal->moverse = false;
		}
	}

	// Tecla dereita: xiro da camara en vistaXeral a dereita
	if (tecla == 262) {
		moverCamara(XIRO_CAMARA_DEREITA);
	}

	// Tecla esquerda: xiro da camara en vistaXeral a esquerda
	if (tecla == 263) {
		moverCamara(XIRO_CAMARA_ESQUERDA);
	}

	// Tecla arriba: xiro da camara en vistaXeral na vertical cara arriba
	if (tecla == 265) {
		moverCamara(XIRO_CAMARA_ARRIBA);
	}

	// Tecla abaixo: xiro da camara en vistaXeral na vertical cara abaixo
	if (tecla == 264) {
		moverCamara(XIRO_CAMARA_ABAIXO);
	}

	// Tecla +: achegase a camara en vistaXeral
	if (tecla == 93 && accion != GLFW_RELEASE) {
		moverCamara(ACERCAR_CAMARA);
	}

	// Tecla -: afastase a camara en vistaXeral
	if (tecla == 47 && accion != GLFW_RELEASE) {
		moverCamara(AFASTAR_CAMARA);
	}
}

void Mundo::moverCamara(int tipoMovemento) {
	switch (tipoMovemento) {
	case XIRO_CAMARA_DEREITA:
		camara->alpha += INCREMENTO_XIRO_CAMARA_XERAL;
		if (camara->alpha >= (float)(2.0 * PI)) {
			camara->alpha -= (float)(2.0 * PI);
		}
			break;
	case XIRO_CAMARA_ESQUERDA:
		camara->alpha -= INCREMENTO_XIRO_CAMARA_XERAL;
		if (camara->alpha <= (float)(-2.0f * PI)) {
			camara->alpha += (float)(2.0f * PI);
		}
		break;
	case XIRO_CAMARA_ARRIBA:
		camara->beta = fmin(camara->beta + INCREMENTO_XIRO_CAMARA_XERAL, PI / 2.0f - UNIDADE_GRAO_EN_RADIANS);
		break;
	case XIRO_CAMARA_ABAIXO:
		// Limite superior de 90 grados
		camara->beta = fmax(camara->beta - INCREMENTO_XIRO_CAMARA_XERAL, 0.0f + UNIDADE_GRAO_EN_RADIANS);
		break;
	case ACERCAR_CAMARA:
		camara->radio = fmax(camara->radio - INCREMENTO_RADIO_CAMARA_XERAL, MIN_DIST_CAMARA_XERAL);
		break;
	case AFASTAR_CAMARA:
		camara->radio = fmin(camara->radio + INCREMENTO_RADIO_CAMARA_XERAL, MAX_DIST_CAMARA_XERAL);
		break;
	}
}

