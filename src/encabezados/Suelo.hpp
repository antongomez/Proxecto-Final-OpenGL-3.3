#pragma once 

#include "Figura.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Suelo
{
public:
	// Atributos
	glm::vec3 posicion;	// Posicion na que se vai situar o chan
	float escala;		// tamanho dos cadrados do chan
	float limites[2];	// Limite inferior e superior do chan
	glm::mat4 matrizModelo; // Matriz que representa a transformacion linear que se aplica sobre cada cadrado do chan
	

	unsigned int shaderProgram;

	Figura* fg;
	Figura* fgMuro;

	// Construtores
	Suelo(glm::vec3 posicion, float escala, float* limites, unsigned int shaderProgram, int tipoFigura, std::string rutaTextura, std::string rutaTexturaMuro);

	// Metodos
	void renderizarSuelo();
};