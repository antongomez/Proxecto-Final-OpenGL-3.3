#pragma once 

#include "Suelo.hpp"
#include "PersonaxePrincipal.hpp"
#include "Camara.hpp"
#include "Luz.hpp"

#include <vector>
#include <map>
#include <glm/glm.hpp>
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

	PantallaInicial(PersonaxePrincipal* personaxe, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
		float* limites, std::map<int, std::vector<Luz*>> luces,
		std::string rutaTexturaSuelo, std::string rutaTexturaMetalica);
	PantallaInicial(PersonaxePrincipal* personaxe, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
		std::map<int, std::vector<Luz*>> luces);

	virtual void iniciar(float width, float height);
	virtual void moverObxectos(float tempoTranscurrido);
	virtual void renderizarEscena();
	virtual void eventoTeclado(int tecla, int accion);
	virtual void reescalarVenta(GLFWwindow* window, int width, int height);
	virtual bool mundoCompletado();

protected:
	void establecerLucesShader(GLuint shader);
	void xerarSuelo(float* limites, std::string rutaTexturaSuelo);

};