#pragma once 

#include "Figura.hpp"

#include <glm/glm.hpp>

class Obxecto
{
public:
	// Atributos
	glm::vec3 posicion; // Determina a traslacion para posicionar ao obxecto
	glm::vec3 escalado; // Determina o escalado para redimensionar o obxecto
	float angulo;		// Determina o angulo de rotacion do obxecto
	glm::mat4 matrizModelo; // Matriz que representa a transformacion linear que se aplica sobre o obxecto
	Figura* fg; // Obxecto que se encarga de debuxar
	bool hittable;//Sera 1 para elementos decorativos con los que se pueda chocar

	unsigned int shaderProgram;


	// Construtores
	// Para as figuras xeometricas (como os cadrados)
	Obxecto(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, int tipoFigura);
	// Non crea unha instacia para o atributo fg
	Obxecto(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram);
	// Para os elementos decorativos
	Obxecto(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, std::string inputOBJfile);
	// Para os elementos decorativos
	Obxecto(glm::vec3 posicion, glm::vec3 escalado, float angulo, unsigned int shaderProgram, std::string inputOBJfile, bool hittable);


	// Metodos
	void renderizarObxecto();
	virtual void calcularMatrizModelo();
};