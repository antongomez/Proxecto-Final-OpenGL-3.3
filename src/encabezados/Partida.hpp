#pragma once 

#include "PersonaxePrincipal.hpp"
#include "Mundo.hpp"

#include <glm/glm.hpp>

#include <vector>

class Partida
{
public:
	// Atributos
	PersonaxePrincipal* personaxePrincipal;
	std::vector<Mundo*> mundos;
	int idMundoActual;
	// Luces

	GLuint shaderProgram;

	// Construtores
	Partida(GLuint shaderProgram);

	// Metodos
	void iniciarPartida();
	//Move e renderiza os obxectos
	void moverObxectos(float tempoTranscurrido);
	void reescalarVenta(GLFWwindow* window, int width, int height);
	void eventoTeclado(int tecla, int accion);
	void finalizarMundo();
	void seguinteMundo();
	
};