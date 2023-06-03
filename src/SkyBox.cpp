#include "encabezados/SkyBox.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad.h>

SkyBox::SkyBox(float distancia, float altura, unsigned int shaderProgram, int tipoFigura, std::string rutaTexturas[4]) {
	this->distancia = distancia + 4.0f * (1 / ESCALA_SUELO);
	this->altura = altura + distancia / 6.0f; // Subimos un pouco o skybox

	this->shaderProgram = shaderProgram;

	// Creamos os catro cadrados e cargamos as suas texturas
	for (int i = 0; i < 4; i++) {
		this->fg[i] = new Figura(tipoFigura, shaderProgram);
	}

	// Orde dos cadrados: left, right, front, back
	this->fg[0]->cargarTextura(rutaTexturas[0].c_str(), GL_RGB);
	this->fg[1]->cargarTextura(rutaTexturas[1].c_str(), GL_RGB);
	this->fg[2]->cargarTextura(rutaTexturas[2].c_str(), GL_RGB);
	this->fg[3]->cargarTextura(rutaTexturas[3].c_str(), GL_RGB);
}

void SkyBox::renderizarSkyBox() {

	// Calculamos as rotacion e traslacions de cada cadrado do skyBox 
	// O escalado e o mesmo para os catro
	glm::mat4 transformacions[4];

	// Left
	transformacions[0] = glm::mat4();
	transformacions[0] = glm::translate(transformacions[0], glm::vec3(-distancia, altura, 0));
	transformacions[0] = glm::rotate(transformacions[0], (float)(PI / 2.0), glm::vec3(0.0, 1.0, 0.0));

	// Right
	transformacions[1] = glm::mat4();
	transformacions[1] = glm::translate(transformacions[1], glm::vec3(distancia, altura, 0));
	transformacions[1] = glm::rotate(transformacions[1], (float)(-PI / 2.0), glm::vec3(0.0, 1.0, 0.0));

	// Front
	transformacions[2] = glm::mat4();
	transformacions[2] = glm::translate(transformacions[2], glm::vec3(0, altura, distancia));
	transformacions[2] = glm::rotate(transformacions[2], (float)PI, glm::vec3(0.0, 1.0, 0.0));

	// Back
	transformacions[3] = glm::mat4();
	transformacions[3] = glm::translate(transformacions[3], glm::vec3(0, altura, -distancia));


	for (int i = 0; i < 4; i++) {
		// Usamos a textura correspondente para cada cadrado
		glBindTexture(GL_TEXTURE_2D, fg[i]->textura);

		transformacions[i] = glm::scale(transformacions[i], glm::vec3(distancia * 2.0f));

		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformacions[i]));

		fg[i]->renderizar();
	}

}