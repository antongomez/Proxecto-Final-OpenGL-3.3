#pragma once 

#include "Obxecto.hpp"

class PersonaxePrincipal : public Obxecto
{
public:
	// Atributos
	bool moverse;

	// Construtores
	PersonaxePrincipal(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, int tipoFigura);

	// Metodos
	void moverPersonaxe(double tempoTranscurrido);
	void calcularMatrizModelo() override;
};