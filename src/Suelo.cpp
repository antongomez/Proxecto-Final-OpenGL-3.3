#include "encabezados/Suelo.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad.h>

Suelo::Suelo(glm::vec3 posicion, float escala, float limitesx[], float limitesz[], unsigned int shaderProgram, int tipoFigura) {
	this->posicion = posicion;
	this->escala = escala;

	for (int i = 0; i < 2; i++) {
		this->limitesx[i] = limitesx[i];
		this->limitesz[i] = limitesz[i];
	}

	this->shaderProgram = shaderProgram;

	this->fg = new Figura(tipoFigura, shaderProgram);
}

void Suelo::renderizarSuelo() {
	float i, j;
	float escalado = (float)1.0 / escala;

	for (i = limitesx[0]; i <= limitesx[1]; i += (float)(1.0 / escala)) {
		for (j = limitesz[0]; j <= limitesz[1]; j += (float)(1.0 / escala)) {
			matrizModelo = glm::mat4();
			matrizModelo = glm::rotate(matrizModelo, (float)(-PI / 2.0), glm::vec3(1.0, 0.0, 0.0));
			matrizModelo = glm::translate(matrizModelo, glm::vec3(i + posicion.x, j + posicion.z, posicion.y));
			matrizModelo = glm::scale(matrizModelo, glm::vec3(escalado));

			unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrizModelo));

			fg->renderizar();
		}
	}
}