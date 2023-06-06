#pragma once 

#include "Obxecto.hpp"
#include <glm/gtc/type_ptr.hpp> 

class Enemigo : public Obxecto
{
public:
	// Atributos
	int nivel;		// Nivel do inimigo que determinara a velocidade a que se achega
	Obxecto* target;	// Obxecto ao que se achega o enemigo
	glm::vec2 direccion;

	int estado;	// 0 muerto, 1 vivo, 2 semivivo
	int instantes_animacion; // Instantes que lleva ejecutandose su animacion de muerte

	// Construtores
	Enemigo(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, int tipoFigura, int nivel, Obxecto* target);

	// Metodos
	void moverEnemigo(double tempoTranscurrido);
	void calcularMatrizModelo() override;
};