#pragma once

class FigurasXeometricas
{
public:

	//Atributos
	unsigned int VAOEixos;
	unsigned int VAOCadrado;
	unsigned int VAOCubo;
	unsigned int VAOEsfera;

	// Construtores
	FigurasXeometricas();
	// Destrutor
	~FigurasXeometricas();

	// Metodos
	void debuxaEixos();
	void renderizarEixos();
	void debuxaCadrado();
	void renderizarCadrado();
	void debuxaCubo();
	void renderizarCubo();
	//void debuxaEsfera();
	
};