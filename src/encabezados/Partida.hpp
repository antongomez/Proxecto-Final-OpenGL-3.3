#pragma once 

#include "PersonaxePrincipal.hpp"
#include "Mundo.hpp"
#include "PantallaInicial.hpp"

#include <glm/glm.hpp>

#include <vector>

class Partida
{
public:
	// Atributos
	PersonaxePrincipal* personaxePrincipal;
	std::vector<PantallaInicial*> mundos;
	int idMundoActual;

	GLuint shaderProgram;
	GLuint shaderProgramTex;
	GLuint shaderProgramMiniMapa;

	// Construtores
	Partida(GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramMiniMapa);

	// Metodos
	void iniciarPartida();
	//Move e renderiza os obxectos
	void moverObxectos(float tempoTranscurrido);
	void reescalarVenta(GLFWwindow* window, int width, int height);
	void eventoTeclado(GLFWwindow* window, int tecla, int accion);
	void seguinteMundo();

	bool reiniciarPartida;

private:
	double tempoInicioPartida;
	double tempoPartida;

	void iniciarMusica();
	
};