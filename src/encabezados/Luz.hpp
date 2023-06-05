#pragma once 

#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Luz
{
public:
	// Atributos
	glm::vec3 posicion;
	glm::vec3 direccion;

	glm::vec3 posicionInicial;
	glm::vec3 direccionInicial;

	float constante;
	float linear;
	float cuadratico;

	glm::vec3 ambiente;
	glm::vec3 difusa;
	glm::vec3 especular;

	float innerCutOff;
	float outerCutOff;

	bool mobil;
	
	// Construtores
	Luz(glm::vec3 direccion, glm::vec3 ambiente, glm::vec3 difusa, glm::vec3 especular);
	Luz(glm::vec3 posicionInicial, glm::vec3 direccionInicial, glm::vec3 difusa, glm::vec3 especular, float innerCutOff, float outerCutOff, bool mobil);
	Luz(glm::vec3 posicion, glm::vec3 ambiente, glm::vec3 difusa, glm::vec3 especular, float constante, float linear, float cuadratico);

	// Metodos
	void actualizarLuz(glm::vec3 pos, float angulo);
};