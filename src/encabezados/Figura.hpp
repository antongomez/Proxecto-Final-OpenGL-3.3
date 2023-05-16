#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>

class Figura
{
public:

	//Atributos
	unsigned int* VAO;
	int tipo;
	std::map<int, std::vector<glm::vec3>> vertices;
	std::map<int, std::vector<glm::vec3>> normais;

	// Construtores
	Figura(int tipo);
	Figura(int tipo, std::string inputOBJfile);
	// Destrutor
	~Figura();

	// Metodos
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