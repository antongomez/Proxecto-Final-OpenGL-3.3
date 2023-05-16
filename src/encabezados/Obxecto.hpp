#pragma once 

#include "FigurasXeometricas.hpp"

#include <glm/glm.hpp>

class Obxecto
{
public:
	// Atributos
	glm::vec3 posicion; // Determina a traslacion para posicionar ao obxecto
	glm::vec3 escalado; // Determina o escalado para redimensionar o obxecto
	glm::mat4 matrizModelo; // Matriz que representa a transformacion linear que se aplica sobre o obxecto
	FigurasXeometricas* fg; // Obxecto que se encarga de debuxar

	unsigned int shaderProgram;


	// Construtores
	Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, int tipoFigura);
	// Non crea unha instacia para o atributo fg
	Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram);

	// Metodos
	void renderizarObxecto();
	virtual void calcularMatrizModelo();
};