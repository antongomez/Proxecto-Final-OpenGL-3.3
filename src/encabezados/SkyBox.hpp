#pragma once 

#include "Figura.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class SkyBox
{
public:
	// Atributos
	float distancia; // Centro do cubo do skyBox
	float altura; // Altura do mundo do skybox

	unsigned int shaderProgram;

	Figura* fg[4];

	// Construtores
	SkyBox(float distancia, float altura, unsigned int shaderProgram, int tipoFigura, std::string rutaTexturas[4]);

	// Metodos
	void renderizarSkyBox();
};