#include "encabezados/Enemigo.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

Enemigo::Enemigo(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, FigurasXeometricas* fg, int nivel, Obxecto* target) : Obxecto(posicion, escalado, shaderProgram, fg) {
	this->nivel = nivel;
	this->target = target;
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


