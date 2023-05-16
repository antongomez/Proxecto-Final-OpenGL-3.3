#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class FigurasXeometricas
{
public:

	//Atributos
	unsigned int* VAO;
	int tipo;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normais;

	// Construtores
	FigurasXeometricas(int tipo);
	FigurasXeometricas(int tipo, std::string inputOBJfile);
	// Destrutor
	~FigurasXeometricas();

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