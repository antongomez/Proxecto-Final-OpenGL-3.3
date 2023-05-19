#include "encabezados/Partida.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <glad.h>

#include <iostream>

Partida::Partida(GLuint shaderProgram) {
	this->shaderProgram = shaderProgram;
	iniciarPartida();
}

void Partida::iniciarPartida() {
	// Non determinamos a posicion do personaxe principal, pero si o seu escalado. A posicion variara cos mundos pero non a escala
	this->personaxePrincipal = new PersonaxePrincipal(glm::vec3(0, 0, 0), glm::vec3(1.0f), shaderProgram, FIGURA_CARGADA, 0);

	// Creamos os mundos
	float limitesx[] = { -10.0f, 10.0f };
	float limitesz[] = { -10.0f, 10.0f };

	std::map<int, int> elementosDecorativos;
	elementosDecorativos[ID_PEDRA1] = 10;
	elementosDecorativos[ID_PEDRA2] = 2;
	elementosDecorativos[ID_PEDRA3] = 12;
	elementosDecorativos[ID_ARBORE1] = 3;
	elementosDecorativos[ID_HERBA] = 25;
	Mundo* mundo = new Mundo(personaxePrincipal, shaderProgram, 0, limitesx, limitesz, elementosDecorativos, 1);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 10;
	elementosDecorativos[ID_PEDRA2] = 2;
	elementosDecorativos[ID_PEDRA3] = 12;
	elementosDecorativos[ID_ARBORE1] = 3;
	mundo = new Mundo(personaxePrincipal, shaderProgram, -50, limitesx, limitesz, elementosDecorativos, 2);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 10;
	elementosDecorativos[ID_PEDRA2] = 2;
	elementosDecorativos[ID_PEDRA3] = 12;
	elementosDecorativos[ID_ARBORE1] = 3;
	mundo = new Mundo(personaxePrincipal, shaderProgram, -100, limitesx, limitesz, elementosDecorativos, 3);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 10;
	elementosDecorativos[ID_PEDRA2] = 2;
	elementosDecorativos[ID_PEDRA3] = 12;
	elementosDecorativos[ID_ARBORE1] = 3;
	mundo = new Mundo(personaxePrincipal, shaderProgram, -150, limitesx, limitesz, elementosDecorativos, 4);
	mundos.push_back(mundo);

	idMundoActual = 0;
	mundos[0]->iniciarMundo();
}

void Partida::moverObxectos(float tempoTranscurrido) {
	mundos[idMundoActual]->moverObxectos(tempoTranscurrido);
	mundos[idMundoActual]->renderizarEscena();
}

void Partida::reescalarVenta(GLFWwindow* window, int width, int height) {
	mundos[idMundoActual]->reescalarVenta(window, width, height);
}

void Partida::eventoTeclado(int tecla, int accion) {
	// Tecla ñ
	if (tecla == 59 && accion == GLFW_RELEASE) {
		seguinteMundo();
	}
	else if (tecla != 1) {
		mundos[idMundoActual]->eventoTeclado(tecla, accion);
	}
}

void Partida::seguinteMundo() {
	finalizarMundo();
	if (idMundoActual != 3) {
		idMundoActual++;
		mundos[idMundoActual]->iniciarMundo();
	}
	else {
		std::cout << "FIN DE PARTIDA\n";
	}

}

void Partida::finalizarMundo() {

}


