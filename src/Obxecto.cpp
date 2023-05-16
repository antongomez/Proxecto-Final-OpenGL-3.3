#include "encabezados/Obxecto.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

// Constructor para os obxectos que consisten en figuras xeometricas
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, int tipoFigura) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->shaderProgram = shaderProgram;
	this->fg = new Figura(tipoFigura, shaderProgram);
}

// Constructor para os obxectos cargados
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->shaderProgram = shaderProgram;
}

void Obxecto::calcularMatrizModelo() {
	matrizModelo = glm::mat4(); // Matriz identidade
	matrizModelo = glm::translate(matrizModelo, posicion);
	matrizModelo = glm::scale(matrizModelo, escalado);
}

void Obxecto::renderizarObxecto() {
	// Recalculamos a matriz do modelo para aplicar as transformacions
	calcularMatrizModelo();
	
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrizModelo));

	fg->renderizar();
	
}
