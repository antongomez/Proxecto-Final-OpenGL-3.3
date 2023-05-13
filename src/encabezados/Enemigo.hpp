#pragma once 

#include "Obxecto.hpp"

class Enemigo : public Obxecto
{
public:
	// Atributos
	int nivel;		// Nivel do inimigo que determinara a velocidade a que se achega
	Obxecto* target;	// Obxecto ao que se achega o enemigo

	// Construtores
	Enemigo(glm::vec3 posicion, glm::vec3 escalado, unsigned int shaderProgram, FigurasXeometricas* fg, int nivel, Obxecto* target);

	// Metodos
	void moverEnemigo(double tempoTranscurrido);
};