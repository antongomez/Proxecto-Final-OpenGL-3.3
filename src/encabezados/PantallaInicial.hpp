#pragma once 

#include "Suelo.hpp"
#include "PersonaxePrincipal.hpp"
#include "Camara.hpp"
#include "Luz.hpp"

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class PantallaInicial
{
public:
	// Atributos
	Camara* camara;
	Camara* camaraSecundaria;

	Suelo* suelo;

	std::map<int, std::vector<Luz*>> luces;

	PersonaxePrincipal* personaxePrincipal;

	GLuint shaderProgram;
	GLuint shaderProgramTex;
	GLuint shaderProgramBasico;

	bool musica_reproducida;
	int instantes_pausa;

	PantallaInicial(PersonaxePrincipal* personaxe, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
		float* limites, std::map<int, std::vector<Luz*>> luces,
		std::string rutaTexturaSuelo, std::string rutaTexturaMetalica);
	PantallaInicial(PersonaxePrincipal* personaxe, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
		std::map<int, std::vector<Luz*>> luces);

	virtual void iniciar(float width, float height);
	virtual void moverObxectos(float tempoTranscurrido);
	virtual void renderizarEscena(float tempoTranscurrido);
	virtual void eventoTeclado(GLFWwindow* window, int tecla, int accion);
	void reescalarVenta(GLFWwindow* window, int width, int height);
	virtual bool mundoCompletado();
	virtual void finalizarMundo();

protected:
	// Atributos para debuxar a parte de abaixo da venta inicial
	Figura* fg;
	Figura* fgCentro;
	Figura* fgDereita;
	Figura* fgEsquerda;

	void establecerLucesShader(GLuint shader);
	void xerarSuelo(float* limites, std::string rutaTexturaSuelo);

};