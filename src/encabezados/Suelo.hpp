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
	float limitesx[2];	// Limite inferior e superior do chan en x con respecto a posicionx
	float limitesz[2];	// Limite inferior e superior do chan en z con respecto a posicionz
	glm::mat4 matrizModelo; // Matriz que representa a transformacion linear que se aplica sobre cada cadrado do chan
	

	unsigned int shaderProgram;

	Figura* fg;

	// Construtores
	Suelo(glm::vec3 posicion, float escala, float limitesx[], float limitesz[], unsigned int shaderProgram, int tipoFigura);

	// Metodos
	void renderizarSuelo();
};