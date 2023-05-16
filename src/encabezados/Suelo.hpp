#pragma once 

#include "FigurasXeometricas.hpp"

#include <glm/glm.hpp>

class Suelo
{
public:
	// Atributos
	float posicionx;	// Posicion en x na que se vai centrar o chan
	float posicionz;	// Posicion en z na que se vai centrar o chan
	float escala;		// tamanho dos cadrados
	float limitesx[2];	// Limite inferior e superior do chan en x con respecto a posicionx
	float limitesz[2];	// Limite inferior e superior do chan en z con respecto a posicionz
	glm::mat4 matrizModelo; // Matriz que representa a transformacion linear que se aplica sobre cada cadrado do chan
	

	unsigned int shaderProgram;

	FigurasXeometricas* fg;

	// Construtores
	Suelo(float posicionx, float posicionz, float escala, float limitesx[], float limitesz[], unsigned int shaderProgram, int tipoFigura);

	// Metodos
	void renderizarSuelo();
};