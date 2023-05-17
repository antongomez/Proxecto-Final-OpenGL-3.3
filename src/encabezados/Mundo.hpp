#pragma once 

#include "Suelo.hpp"
#include "Enemigo.hpp"
#include "PersonaxePrincipal.hpp"
#include "Camara.hpp"

#include <vector>
#include <glm/glm.hpp>

class Mundo
{
public:
	// Atributos
	Suelo *suelo;
	std::vector<Obxecto*> elementosDecorativos;
	std::vector<Enemigo*> inimigos;
	PersonaxePrincipal* personaxePrincipal;
	Camara *camara;

	GLuint shaderProgram;

	// Construtores
	Mundo(PersonaxePrincipal* personaxe, GLuint shaderProgram, float alturaMundo, float* limitesx, float* limitesz, int numElementosDecorativos, int nivelMundo);

	// Destructor

	// Metodos
	void iniciarMundo();
	void xerarSuelo(float alturaMundo, float* limitesx, float* limitesz);
	void xerarElementosDecorativos(int numElementosDecorativos);
	void xerarInimigos(int nivelMundo);
	void moverObxectos(float tempoTranscurrido);
	void renderizarEscena();
	void eventoTeclado(int tecla, int accion);
	void reescalarVenta(GLFWwindow* window, int width, int height);
	void establecerCamara(int tipoCamara, glm::vec3 target);
	void moverCamara(int tipoMovemento);
};