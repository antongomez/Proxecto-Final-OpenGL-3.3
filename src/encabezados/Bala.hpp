#pragma once 

#include "Obxecto.hpp"
#include <glm/gtc/type_ptr.hpp> 

class Bala : public Obxecto
{
public:
	// Atributos
	glm::vec3 direccion;

	// Construtores
	Bala(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, std::string inputOBJfile, glm::vec3 direccion);

	// Metodos
	bool moverBala(double tempoTranscurrido, float* limites);
};