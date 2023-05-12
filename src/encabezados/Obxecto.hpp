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

	unsigned int shaderProgram;

	FigurasXeometricas* fg;

	// Construtores
	Obxecto(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, FigurasXeometricas* fg);

	// Metodos
	void renderizarObxecto();

private:
	void calcularMatrizModelo();
};