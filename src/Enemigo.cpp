#include "encabezados/Enemigo.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <glad.h>

Enemigo::Enemigo(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, int tipoFigura, int nivel, Obxecto* target) : Obxecto(posicion, escalado, shaderProgram) {
	this->nivel = nivel;
	this->target = target;
	this->direccion = glm::vec2(1, 0); // Os trolls empezan mirando nesta direccion
	this->fg = new Figura(FIGURA_CARGADA, shaderProgram, "recursos/modelos/troll.obj");
}

void Enemigo::moverEnemigo(double tempoTranscurrido) {
	// Adecuamos a velocidade do enemigo ao nivel
	float velocidade = nivel * VELOCIDADE_BASE_ENEMIGOS;

	// Calculamos a direccion do enemigo (normalizada)
	glm::vec3 direccion = glm::normalize(target->posicion - posicion);
	// Calculamos o desprazamento en funcion do tempo que transcurriu dende a ultima vez que o movimos
	float desprazamento = (float)tempoTranscurrido * velocidade;

	// Actualizamos a posicion do enemigo
	posicion += desprazamento * direccion;
}

void Enemigo::calcularMatrizModelo() {
	matrizModelo = glm::mat4(); // Matriz identidade
	matrizModelo = glm::translate(matrizModelo, posicion);

	// Calculamos o angulo que debe xirar para mirar ao personaxe principal.
	// Facemolo en duas dimensions
	glm::vec2 posicionTarget(target->posicion.x, target->posicion.z);
	glm::vec2 posicionTroll(posicion.x, posicion.z);
	glm::vec2 novadireccion = glm::normalize(posicionTarget - posicionTroll);
	// Ambos vectores estan normalizados, co que o seu modulo e 1
	float angulo = acos(glm::dot(novadireccion, direccion));
	// Axustamos en que direccion xiramos en funcion da poisicion do Troll
	// Considerando como orixe o punto no plano onde se atopa o tanque:
	//		No 1 e 2 cuadrante, xiramos en sentido horario (angulo negativo)
	//		No 3 e 4 cuadrante, xiramos en sentido antihorario (angulo positivo)
	if (posicionTarget.y < posicionTroll.y) {
		angulo = -angulo;
	}
	matrizModelo = glm::rotate(matrizModelo, -angulo, glm::vec3(0, 1, 0));
	matrizModelo = glm::scale(matrizModelo, escalado);
}


