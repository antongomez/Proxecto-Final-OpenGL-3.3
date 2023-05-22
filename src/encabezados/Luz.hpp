#pragma once 

#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Luz
{
public:
	// Atributos
	glm::vec3 posicion;
	glm::vec3 direccion;

	glm::vec3 ambiente;
	glm::vec3 difusa;
	glm::vec3 especular;

	float cutOff;

	
	// Construtores
	Luz(glm::vec3 direccion, glm::vec3 ambiente, glm::vec3 difusa, glm::vec3 especular);
	Luz(glm::vec3 posicion, glm::vec3 direccion, glm::vec3 difusa, glm::vec3 especular, float cutOff);

	// Metodos
	void xirarDireccionLuz(float angulo);
};