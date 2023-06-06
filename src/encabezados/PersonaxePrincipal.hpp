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
	std::vector<float> anchoTanques;std::vector<std::pair<float, float>> dimensionsTanques;
	std::vector<std::string> nomesTanques;
	float largo;
	float ancho;
	float limites[2];

	// Construtores
	PersonaxePrincipal(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, int tipoFigura, 
		std::vector<std::string> rutasPersonaxes, std::vector<std::pair<float, float>> dimensionsTanques,
		std::vector<std::string> nomesTanques, float* limites);

	// Metodos
	void moverPersonaxe(double tempoTranscurrido, std::vector<Obxecto*> obxectosDecorativos);
	void calcularMatrizModelo() override;
	void disparar();
	void renderizarBalas();
	// Se seguinte e true, cambiamos ao seguinte personaxe, senon, cambiamos ao anterior
	void cambiarPersonaxe(bool seguinte);
	std::string nomeTanqueActual();

	bool colisionArbol(std::vector<Obxecto*> obxectosDecorativos);

private:
	void moverBalas(double tempoTranscurrido);
};