#include "encabezados/Bala.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <glad.h>

Bala::Bala(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, std::string inputOBJfile, glm::vec3 direccion) : Obxecto(posicion, escalado, angulo, shaderProgram, inputOBJfile) {
	this->direccion = direccion;
}

bool Bala::moverBala(double tempoTranscurrido, float* limites) {
	float desprazamento = (float)tempoTranscurrido * VELOCIDADE_BASE_BALA;
	posicion += desprazamento * direccion;

	// Comprobamos que non saia do muro
	return !(posicion.x >= limites[0] && posicion.x <= limites[1] &&
		posicion.z >= limites[0] && posicion.z <= limites[1]);
}


