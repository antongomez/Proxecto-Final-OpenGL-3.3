#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>

#include "tiny_obj_loader.h"

class Figura
{
public:

	// -------------- Atributos -----------------//
	unsigned int* VAO;
	// FIGURA_CADRADO, FIGURA_CUBO, FIGURA_CARGADA
	int tipo;
	// Almacenamos os materiais do modelo
	std::vector<tinyobj::material_t> materiais;
	// Almacenamos os vertices agrupados por material
	std::map<int, std::vector<glm::vec3>> vertices;
	// Almacenamos as normais agrupadas por material
	std::map<int, std::vector<glm::vec3>> normais;
	// ShaderProgram que usa
	unsigned int shaderProgram;
	// Textura da figura
	unsigned int textura;

	// -------------- Construtores -----------------//
	
	// Construtor para as figuras xeometricas
	Figura(int tipo, unsigned int shaderProgram);
	// Construtor para as figuras cargadas
	Figura(int tipo, unsigned int shaderProgram, std::string inputOBJfile);
	// Destrutor
	~Figura();

	// -------------- Meotodos -----------------//
	void debuxar();
	void renderizar();

	void cargarTextura(const char* nombreTextura, int formato);

private:

	void debuxaEixos();
	void renderizarEixos();

	void debuxaCadrado();
	void renderizarCadrado();

	void debuxaCubo();
	void renderizarCubo();

	void cargarModelo(std::string inputOBJfile);
	void debuxaFiguraCargada();
	void renderizarFiguraCargada();
	
};