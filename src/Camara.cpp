#include "encabezados/Camara.hpp"
#include "encabezados/definicions.h"

#include <math.h>

#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Camara::Camara(float radio, float alpha, float beta, GLuint shaderProgram) {
	this->shaderProgram = shaderProgram;
	this->radio = radio;
	this->alpha = alpha;
	this->beta = beta;
	this->width = SCR_WIDTH;
	this->height = SCR_HEIGHT;
	this->modo = MODO_CAMARA_VISTA_XERAL;
	this->posicionCamara = glm::vec3(0, 0, 0);
}

void Camara::establecerCamara(PersonaxePrincipal *p) {
	switch (modo) {
	case MODO_CAMARA_VISTA_XERAL:
		vistaXeral(p);
		break;
	case MODO_CAMARA_TERCEIRA_PERSOA:
		vistaTerceiraPersoa(p);
		break;
	case MODO_CAMARA_PRIMEIRA_PERSOA:
		vistaPrimeiraPersoa(p);
		break;
	}
}

void Camara::vistaPrimeiraPersoa(PersonaxePrincipal* p)
{
	// d1: distancia cara atras que se bota a camara
	// d2: distancia a que apunta a camara con respecto da posicion do obxecto ao que segue
	float d2 = 5.0f, d1 = 2.0f;
	// Alura a que situamos a camara
	float alturaCamara = 1.1f;
	// A camara debe rotar co obxecto que segue
	float angulo = p->angulo;

	posicionCamara = p->posicion + glm::vec3(d1 * sin(angulo), alturaCamara, d1 * cos(angulo));

	// Matriz de vista
	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		posicionCamara,
		p->posicion + glm::vec3(d2 * sin(angulo), alturaCamara, d2 * cos(angulo)),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Camara::vistaXeral(PersonaxePrincipal* p)
{
	posicionCamara = glm::vec3(radio * sin(alpha) * cos(beta), radio * sin(beta), radio * cos(alpha) * cos(beta));

	// Matriz de vista
	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		posicionCamara,
		p->posicion,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Camara::vistaTerceiraPersoa(PersonaxePrincipal* p)
{
	// d1: distancia cara atras que se bota a camara
	// d2: distancia a que apunta a camara con respecto da posicion do obxecto ao que segue
	float d1 = 4.0f, d2 = 5.0f;
	// Definimos a altura da camara con respecto da posicion do obxecto ao que segue
	float alturaCamara = 2.0f;
	// A camara debe rotar co obxecto que segue
	float angulo = p->angulo;

	posicionCamara = p->posicion + glm::vec3(-d1 * sin(angulo), alturaCamara, -d1 * cos(angulo));
	glm::vec3 lookAt = p->posicion + glm::vec3(d2 * sin(angulo), 0, d2 * cos(angulo));

	// Matriz de vista
	glm::mat4 view;
	view = glm::mat4();
	view = glm::lookAt(
		posicionCamara,
		lookAt,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Camara::actualizarMatrizProxeccion() {

	glm::mat4 projection;
	projection = glm::mat4();
	projection = glm::perspective(
		glm::radians(60.0f),
		width / height,
		NEAR, FAR
	);
	unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}