#include "encabezados/Luz.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

// Construtor para as luces direcionais
Luz::Luz(glm::vec3 direccion, glm::vec3 ambiente, glm::vec3 difusa, glm::vec3 especular) {
	this->direccion = direccion;
	this->ambiente = ambiente;
	this->difusa = difusa;
	this->especular = especular;
}

// Construtor para as luces focais
Luz::Luz(glm::vec3 posicion, glm::vec3 direccion, glm::vec3 difusa, glm::vec3 especular, float innerCutOff, float outerCutOff) {
	this->posicion = posicion;
	this->direccion = direccion;
	this->difusa = difusa;
	this->especular = especular;
	this->innerCutOff = innerCutOff;
	this->outerCutOff = outerCutOff;
}

void Luz::actualizarLuz(glm::vec3 pos, float angulo) {
	posicion = pos + glm::vec3(0, 2, 0);
	glm::mat4 rotacion = rotate(glm::mat4(), angulo, glm::vec3(0, 1, 0));
	direccion = rotacion * glm::vec4(0, 0, 1.0f, 0);
}
