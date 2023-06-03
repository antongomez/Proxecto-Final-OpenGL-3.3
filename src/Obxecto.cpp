#include "encabezados/Obxecto.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

// Constructor para os obxectos que consisten en figuras xeometricas
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, int tipoFigura) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->shaderProgram = shaderProgram;
	this->fg = new Figura(tipoFigura, shaderProgram);
	// Por defecto a forma do obxecto no minimapa e no mundo real e a mesma
	this->fgMiniMapa = fg;
}

// Constructor para os obxectos cargados
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->shaderProgram = shaderProgram;
}

// Constructor para os elementos decorativos
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, std::string inputOBJfile) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->shaderProgram = shaderProgram;
	this->fg = new Figura(FIGURA_CARGADA, shaderProgram, inputOBJfile);
	// Por defecto a forma do obxecto no minimapa e no mundo real e a mesma
	this->fgMiniMapa = fg;
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

void Obxecto::calcularMatrizModeloMiniMapa() {
	calcularMatrizModelo();
}

void Obxecto::renderizarObxectoMiniMapa() {
	// Recalculamos a matriz do modelo para aplicar as transformacions
	calcularMatrizModeloMiniMapa();

	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrizModelo));

	fgMiniMapa->renderizar();

}
