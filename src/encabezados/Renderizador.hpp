#pragma once 

#include "Obxecto.hpp"
#include "Camara.hpp"

#include <vector>
#include <glm/glm.hpp>

class Renderizador
{
public:
	// Atributos
	std::vector<Obxecto*> escena;
	Camara *camara;

	unsigned int shaderProgram;

	// Construtores
	Renderizador();

	// Destructor

	// Metodos
	void introducirElementoEscena(Obxecto* obxecto);
	void renderizarEscena();
	void establecerCamara(int tipoCamara, glm::vec3 target);
	void reescalarVenta(GLFWwindow* window, int width, int height);
	void setShaderProgram(unsigned int shaderPorgram);
	void moverCamara(int tipoMovemento);
};