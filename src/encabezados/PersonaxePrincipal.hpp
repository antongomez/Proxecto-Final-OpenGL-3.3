#pragma once 

#include "Obxecto.hpp"

class PersonaxePrincipal : public Obxecto
{
public:
	// Atributos
	float angulo;
	bool moverse;

	// Construtores
	PersonaxePrincipal(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, FigurasXeometricas* fg, float angulo);

	// Metodos
	void moverPersonaxe(double tempoTranscurrido);
	void calcularMatrizModelo() override;
};