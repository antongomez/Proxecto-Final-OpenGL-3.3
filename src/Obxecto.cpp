#include "encabezados/Obxecto.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, FigurasXeometricas* fg) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->shaderProgram = shaderProgram;
	this->fg = fg;
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

	fg->renderizarCubo();
	
}
