#include "encabezados/FigurasXeometricas.hpp"
#include "encabezados/definicions.h"

#include <glad.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

FigurasXeometricas::FigurasXeometricas(int tipo) {
	this->tipo = tipo;
	// Debuxamos o tipo de figura (xeometrica, inimigo,...) que corresponda
	debuxar();
}

FigurasXeometricas::~FigurasXeometricas() {
	glDeleteVertexArrays(1, &VAO);
}

void FigurasXeometricas::debuxar() {
	switch (tipo) {
	case FIGURA_EIXOS:
		debuxaEixos();
		break;
	case FIGURA_CADRADO:
		debuxaCadrado();
		break;
	case FIGURA_CUBO:
		debuxaCubo();
		break;
	case FIGURA_INIMIGO:
		debuxaFiguraCargada();
		break;
	default:	// Por defecto debuxamos un cubo
		debuxaCubo();
		break;
	}
}

void FigurasXeometricas::renderizar() {
	switch (tipo) {
	case FIGURA_EIXOS:
		renderizarEixos();
		break;
	case FIGURA_CADRADO:
		renderizarCadrado();
		break;
	case FIGURA_CUBO:
		renderizarCubo();
		break;
	case FIGURA_INIMIGO:
		renderizarFiguraCargada();
		break;
	}
}


void FigurasXeometricas::debuxaEixos() {
	unsigned int VBO, EBO;
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		//Vertices          //Colores
		0.0f, 0.0f, 0.0f,	 1.0f, 1.0f, 1.0f,  // 0
		2.0f, 0.0f, 0.0f,	 0.0f, 1.0f, 1.0f, //x
		0.0f, 2.0f, 0.0f,	 1.0f, 0.0f, 1.0f,// y
		0.0f, 0.0f, 2.0f,	 1.0f, 1.0f, 0.0f, // z  
		2.0f ,2.0f, 2.0f,	 1.0f, 1.0f, 1.0f
	};
	unsigned int indices[] = {  // empieza desde cero
		0, 1,
		0, 2,
		0, 3,
		0, 4
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// position Color

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void FigurasXeometricas::renderizarEixos() {
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
}

void FigurasXeometricas::debuxaCadrado() {
	unsigned int VBO;


	float vertices[] = {
		-0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,

		 -0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, .0f, 1.0f,  0.0f, 1.0f

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Determinamos a posicion dos vertices no array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Determinamos a posicion das cores no array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Determinamos a posicion dos vectores normais no array
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Determinamos a posicion das texturas no array
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);

}

void FigurasXeometricas::renderizarCadrado() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FigurasXeometricas::debuxaCubo() {
	unsigned int VBO, EBO;

	float n = 0.577350f;	// Este valor es 1/sqrt(3)

	float vertices[] = {
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,  -n, -n, n,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,  n, -n, n,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,  n, n, n,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,1.0f,  -n, n, n,

		-0.5f, -0.5f,  -0.5f, 1.0f, 0.0f,0.0f,  -n, -n, -n,
		 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f,0.0f,  n, -n, -n,
		 0.5f,  0.5f,  -0.5f, 0.0f, 0.0f,1.0f,  n, n, -n,
		-0.5f,  0.5f,  -0.5f, 0.0f, 1.0f,1.0f,  -n, n, -n
	};

	unsigned int indices[] = {
		// Cara frontal
		0, 1, 2,
		0, 2, 3,

		// Cara de atrás
		4, 7, 6,
		4, 6, 5,

		// Cara superior
		2, 6, 3,
		3, 6, 7,

		// Cara inferior
		0, 4, 1,
		1, 4, 5,

		// Cara dereita
		1, 5, 2,
		5, 6, 2,

		// Cara esquerda
		0, 3, 4,
		4, 3, 7

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// posicion vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// normais
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void FigurasXeometricas::renderizarCubo() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void FigurasXeometricas::debuxaFiguraCargada() {
	
}

void FigurasXeometricas::renderizarFiguraCargada() {
	
}