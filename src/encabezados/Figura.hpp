#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>

class Figura
{
public:

	// -------------- Atributos -----------------//
	unsigned int* VAO;
	// FIGURA_CADRADO, FIGURA_CUBO, FIGURA_CARGADA
	int tipo;
	// Almacenamos os vertices agrupados por material
	std::map<int, std::vector<glm::vec3>> vertices;
	// Almacenamos as normais agrupadas por material
	std::map<int, std::vector<glm::vec3>> normais;

	// -------------- Construtores -----------------//
	
	// Construtor para as figuras xeometricas
	Figura(int tipo);
	// Construtor para as figuras cargadas
	Figura(int tipo, std::string inputOBJfile);
	// Destrutor
	~Figura();

	// -------------- Meotodos -----------------//
	void debuxar();
	void renderizar();

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