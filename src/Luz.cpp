#include "encabezados/Luz.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

Luz::Luz(glm::vec3 direccion, glm::vec3 ambiente, glm::vec3 difusa, glm::vec3 especular) {
	this->direccion = direccion;
	this->ambiente = ambiente;
	this->difusa = difusa;
	this->especular = especular;
}

Luz::Luz(glm::vec3 posicion, glm::vec3 direccion, glm::vec3 difusa, glm::vec3 especular, float cutOff) {
	this->posicion = posicion;
	this->direccion = direccion;
	this->difusa = difusa;
	this->especular = especular;
	this->cutOff = cutOff;
}

void Luz::xirarDireccionLuz(float angulo) {
	glm::mat4 rotacion = rotate(glm::mat4(), angulo, glm::vec3(0, 1, 0));
	direccion = rotacion * glm::vec4(direccion, 0);
}
