#include "encabezados/Suelo.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad.h>

Suelo::Suelo(glm::vec3 posicion, float escala, float* limites, unsigned int shaderProgram, int tipoFigura, std::string rutaTextura) {
	this->posicion = posicion;
	this->escala = escala;


	this->limites[0] = limites[0];
	this->limites[1] = limites[1];

	this->shaderProgram = shaderProgram;

	this->fg = new Figura(tipoFigura, shaderProgram);
	this->fg->cargarTextura(rutaTextura.c_str(), GL_RGB);
}

void Suelo::renderizarSuelo() {

	float escalado = (float)1.0 / escala;

	glBindTexture(GL_TEXTURE_2D, fg->textura);

	for (float i = limites[0]; i <= limites[1]; i += (float)(1.0 / escala)) {
		for (float j = limites[0]; j <= limites[1]; j += (float)(1.0 / escala)) {
			matrizModelo = glm::mat4();
			matrizModelo = glm::translate(matrizModelo, glm::vec3(i + posicion.x, posicion.y, j + posicion.z));
			matrizModelo = glm::rotate(matrizModelo, (float)(-PI / 2.0), glm::vec3(1.0, 0.0, 0.0));
			matrizModelo = glm::scale(matrizModelo, glm::vec3(escalado));

			unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrizModelo));

			fg->renderizar();
		}
	}
}