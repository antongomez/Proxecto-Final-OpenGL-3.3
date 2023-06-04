#pragma once 

#include "Obxecto.hpp"
#include "Bala.hpp"

class PersonaxePrincipal : public Obxecto
{
public:
	// Atributos
	bool moverse;
	std::vector<Bala*> balas;

	// Construtores
	PersonaxePrincipal(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, int tipoFigura);

	// Metodos
	void moverPersonaxe(double tempoTranscurrido);
	void calcularMatrizModelo() override;
	void disparar();
	void renderizarBalas();

private:
	void moverBalas(double tempoTranscurrido);
};