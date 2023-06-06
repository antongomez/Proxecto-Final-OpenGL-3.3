#include "encabezados/Obxecto.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad.h>

// Constructor para os obxectos que consisten en figuras xeometricas
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, int tipoFigura) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->angulo = angulo;
	this->shaderProgram = shaderProgram;
	this->fg = Figura::GetFigura(tipoFigura, shaderProgram, "");
	this->hittable = false;
}

// Constructor para os inimigos e o personaxe principal
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->angulo = angulo;
	this->shaderProgram = shaderProgram;
	this->hittable = false;
	this->fg = 0;
}

// Constructor para os elementos decorativos
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, std::string inputOBJfile) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->angulo = angulo;
	this->shaderProgram = shaderProgram;
	this->fg = Figura::GetFigura(FIGURA_CARGADA, shaderProgram, inputOBJfile);
}

// Constructor para os elementos decorativos
Obxecto::Obxecto(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, std::string inputOBJfile, bool hittable) {
	this->posicion = posicion;
	this->escalado = escalado;
	this->angulo = angulo;
	this->shaderProgram = shaderProgram;
	this->fg = Figura::GetFigura(FIGURA_CARGADA, shaderProgram, inputOBJfile);
	this->hittable = hittable;
}

void Obxecto::calcularMatrizModelo() {
	matrizModelo = glm::mat4(); // Matriz identidade
	matrizModelo = glm::translate(matrizModelo, posicion);
	matrizModelo = glm::rotate(matrizModelo, angulo, glm::vec3(0, 1, 0));
	matrizModelo = glm::scale(matrizModelo, escalado);
}

void Obxecto::renderizarObxecto() {
	// Recalculamos a matriz do modelo para aplicar as transformacions
	calcularMatrizModelo();
	
	unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrizModelo));

	fg->renderizar();
	
}
