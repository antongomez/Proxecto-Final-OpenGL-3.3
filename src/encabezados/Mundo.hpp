#pragma once 

#include "Suelo.hpp"
#include "Enemigo.hpp"
#include "PersonaxePrincipal.hpp"
#include "Camara.hpp"

#include <vector>
#include <map>
#include <glm/glm.hpp>

class Mundo
{
public:
	// Atributos
	Suelo *suelo;
	std::vector<Obxecto*> obxectosDecorativos;
	std::vector<Enemigo*> inimigos;
	PersonaxePrincipal* personaxePrincipal;
	Camara *camara;
	int nivelMundo;

	GLuint shaderProgram;

	// Construtores
	Mundo(PersonaxePrincipal* personaxe, GLuint shaderProgram, float alturaMundo, float* limitesx, float* limitesz, std::map<int, int> elementosDecorativos, int nivelMundo);

	// Destructor

	// Metodos
	void iniciarMundo();
	void xerarSuelo(float alturaMundo, float* limitesx, float* limitesz);
	void xerarElementosDecorativos(std::map<int,int> elementosDecorativos);
	void xerarInimigos(int nivelMundo);
	void moverObxectos(float tempoTranscurrido);
	void renderizarEscena();
	void eventoTeclado(int tecla, int accion);
	void reescalarVenta(GLFWwindow* window, int width, int height);
	void establecerCamara();
	void moverCamara(int tipoMovemento);
};