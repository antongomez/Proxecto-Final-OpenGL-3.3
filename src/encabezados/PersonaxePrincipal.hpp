#pragma once 

#include "Obxecto.hpp"
#include "Bala.hpp"

#include <vector>

class PersonaxePrincipal : public Obxecto
{
public:
	// Atributos
	bool moverse;
	bool marcha_atras;
	bool xirar_dereita;
	bool xirar_esquerda;
	std::vector<Bala*> balas;
	int nPersonaxes;
	std::vector<Figura*> fgPersonaxes;
	int fgActual;
	float largo;
	float ancho;

	// Construtores
	PersonaxePrincipal(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, int tipoFigura, std::vector<std::string> rutasPersonaxes);

	// Metodos
	void moverPersonaxe(double tempoTranscurrido);
	void calcularMatrizModelo() override;
	void disparar();
	void renderizarBalas();
	// Se seguinte e true, cambiamos ao seguinte personaxe, senon, cambiamos ao anterior
	void cambiarPersonaxe(bool seguinte);

private:
	void moverBalas(double tempoTranscurrido);
};