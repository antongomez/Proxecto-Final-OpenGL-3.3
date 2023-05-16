#pragma once

class FigurasXeometricas
{
public:

	//Atributos
	unsigned int VAO;
	int tipo;

	// Construtores
	FigurasXeometricas(int tipo);
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

	void debuxaFiguraCargada();
	void renderizarFiguraCargada();
	
};