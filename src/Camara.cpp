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

Camara::Camara(float radio, float alpha, float beta, float width, float height) {
	this->radio = radio;
	this->alpha = alpha;
	this->beta = beta;
	this->width = width;
	this->height = height;
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
	view = glm::mat4();
	view = glm::lookAt(
		posicionCamara,
		p->posicion + glm::vec3(d2 * sin(angulo), alturaCamara, d2 * cos(angulo)),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Camara::vistaXeral(PersonaxePrincipal* p)
{
	posicionCamara = p->posicion + glm::vec3(radio * sin(alpha) * cos(beta), radio * sin(beta), radio * cos(alpha) * cos(beta));

	// Matriz de vista
	view = glm::mat4();
	view = glm::lookAt(
		posicionCamara,
		p->posicion,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Camara::vistaTerceiraPersoa(PersonaxePrincipal* p)
{
	// d1: distancia cara atras que se bota a camara
	// d2: distancia a que apunta a camara con respecto da posicion do obxecto ao que segue
	float d1 = 5.0f, d2 = 6.0f;
	// Definimos a altura da camara con respecto da posicion do obxecto ao que segue
	float alturaCamara = 2.5f;
	// A camara debe rotar co obxecto que segue
	float angulo = p->angulo;

	posicionCamara = p->posicion + glm::vec3(-d1 * sin(angulo), alturaCamara, -d1 * cos(angulo));
	glm::vec3 lookAt = p->posicion + glm::vec3(d2 * sin(angulo), alturaCamara/3.0f, d2 * cos(angulo));

	// Matriz de vista
	view = glm::mat4();
	view = glm::lookAt(
		posicionCamara,
		lookAt,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Camara::actualizarMatrizProxeccion() {

	projection = glm::mat4();
	projection = glm::perspective(
		glm::radians(60.0f),
		width / height,
		NEAR, FAR
	);
}

void Camara::actualizarMatricesShader(GLuint shader) {
	unsigned int viewLoc = glGetUniformLocation(shader, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	unsigned int projectionLoc = glGetUniformLocation(shader, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}