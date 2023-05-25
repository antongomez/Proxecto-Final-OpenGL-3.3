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
	std::map<int, std::vector<Luz*>> luces;

	elementosDecorativos[ID_PEDRA1] = 10;
	elementosDecorativos[ID_PEDRA2] = 2;
	elementosDecorativos[ID_PEDRA3] = 12;
	elementosDecorativos[ID_ARBORE1] = 3;
	elementosDecorativos[ID_HERBA] = 35;

	std::vector<Luz*> luzDireccional1;
	luzDireccional1.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.4f), glm::vec3(0.9f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional1;

	Mundo* mundo = new Mundo(personaxePrincipal, shaderProgram, 0, limitesx, limitesz, elementosDecorativos, 1, luces);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 30;
	elementosDecorativos[ID_PEDRA2] = 15;
	elementosDecorativos[ID_PEDRA3] = 20;
	elementosDecorativos[ID_ARBORE1] = 0;
	elementosDecorativos[ID_HERBA] = 0;

	std::vector<Luz*> luzDireccional2;
	luzDireccional2.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.4f), glm::vec3(0.9f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional2;

	mundo = new Mundo(personaxePrincipal, shaderProgram, -50, limitesx, limitesz, elementosDecorativos, 2, luces);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 5;
	elementosDecorativos[ID_PEDRA2] = 2;
	elementosDecorativos[ID_PEDRA3] = 10;
	elementosDecorativos[ID_ARBORE1] = 20;
	elementosDecorativos[ID_HERBA] = 20;

	std::vector<Luz*> luzDireccional3;
	luzDireccional3.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.4f), glm::vec3(0.9f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional3;

	mundo = new Mundo(personaxePrincipal, shaderProgram, -100, limitesx, limitesz, elementosDecorativos, 3, luces);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 11;
	elementosDecorativos[ID_PEDRA2] = 5;
	elementosDecorativos[ID_PEDRA3] = 15;
	elementosDecorativos[ID_ARBORE1] = 15;
	elementosDecorativos[ID_HERBA] = 40;

	std::vector<Luz*> luzDireccional4;
	luzDireccional4.push_back(new Luz(glm::vec3(0, -3, 5), glm::vec3(0.0f), glm::vec3(0.3f), glm::vec3(0.1f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional4;
	std::vector<Luz*> luzFocal;
	luzFocal.push_back(new Luz(glm::vec3(0, 2.0f, 0), glm::vec3(0, 0, 1.0f), glm::vec3(0.8f, 0.8f, 0.4f), glm::vec3(1.0f, 1.0f, 0.5f), 0.91f, 0.82f));
	luces[LUZ_FOCAL] = luzFocal;

	mundo = new Mundo(personaxePrincipal, shaderProgram, -150, limitesx, limitesz, elementosDecorativos, 4, luces);
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
	}
	else {
		idMundoActual = 0;
		std::cout << "VOLVEMOS MUNDO1\n";
	}
	mundos[idMundoActual]->iniciarMundo();
}

void Partida::finalizarMundo() {

}


