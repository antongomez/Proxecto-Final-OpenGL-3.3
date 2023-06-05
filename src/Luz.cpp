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
Luz::Luz(glm::vec3 posicionInicial, glm::vec3 direccionInicial, glm::vec3 difusa, glm::vec3 especular, float innerCutOff, float outerCutOff, bool mobil) {
	this->posicionInicial = posicionInicial;
	this->direccionInicial = direccionInicial;
	this->difusa = difusa;
	this->especular = especular;
	this->innerCutOff = innerCutOff;
	this->outerCutOff = outerCutOff;
	this->mobil = mobil;

	if (!mobil) {
		this->posicion = posicionInicial;
		this->direccion = direccionInicial;
	}
}

Luz::Luz(glm::vec3 posicion, glm::vec3 ambiente, glm::vec3 difusa, glm::vec3 especular, float constante, float linear, float cuadratico) {
	this->posicion = posicion;
	this->ambiente = ambiente;
	this->difusa = difusa;
	this->especular = especular;
	this->constante = constante;
	this->linear = linear;
	this->cuadratico = cuadratico;
}

void Luz::actualizarLuz(glm::vec3 pos, float angulo) {
	if (mobil) {
		glm::mat3 rotacion = rotate(glm::mat4(), angulo, glm::vec3(0, 1, 0));
		posicion = pos + rotacion * posicionInicial;
		direccion = rotacion * direccionInicial;
	}

}
