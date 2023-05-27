#include "encabezados/Partida.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <glad.h>

#include <iostream>

Partida::Partida(GLuint shaderProgram, GLuint shaderProgramTex) {
	this->shaderProgram = shaderProgram;
	this->shaderProgramTex = shaderProgramTex;
	iniciarPartida();
}

void Partida::iniciarPartida() {
	// Non determinamos a posicion do personaxe principal, pero si o seu escalado. A posicion variara cos mundos pero non a escala
	this->personaxePrincipal = new PersonaxePrincipal(glm::vec3(0, 0, 0), glm::vec3(1.0f), shaderProgram, FIGURA_CARGADA, 0);

	// Creamos os mundos
	float limites[] = { -25.0f, 25.0f };

	std::map<int, int> elementosDecorativos;
	std::map<int, std::vector<Luz*>> luces;

	elementosDecorativos[ID_PEDRA1] = 30;
	elementosDecorativos[ID_PEDRA2] = 20;
	elementosDecorativos[ID_PEDRA3] = 50;
	elementosDecorativos[ID_ARBORE1] = 20;
	elementosDecorativos[ID_HERBA] = 150;

	std::vector<Luz*> luzDireccional1;
	luzDireccional1.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.7f), glm::vec3(1.0f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional1;

	std::string rutaTexturaSuelo = "recursos/texturas/hierba.bmp";
	std::string rutaTexturasSkyBox[4];
	rutaTexturasSkyBox[0] = "recursos/texturas/left.jpg";
	rutaTexturasSkyBox[1] = "recursos/texturas/right.jpg";
	rutaTexturasSkyBox[2] = "recursos/texturas/front.jpg";
	rutaTexturasSkyBox[3] = "recursos/texturas/back.jpg";

	Mundo* mundo = new Mundo(personaxePrincipal, shaderProgram, shaderProgramTex, 0, limites, elementosDecorativos, 1, luces, rutaTexturasSkyBox, rutaTexturaSuelo);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 30;
	elementosDecorativos[ID_PEDRA2] = 15;
	elementosDecorativos[ID_PEDRA3] = 20;
	elementosDecorativos[ID_ARBORE1] = 0;
	elementosDecorativos[ID_HERBA] = 0;

	std::vector<Luz*> luzDireccional2;
	luzDireccional2.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.8f), glm::vec3(1.0f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional2;

	rutaTexturaSuelo = "recursos/texturas/sand.jpg";

	mundo = new Mundo(personaxePrincipal, shaderProgram, shaderProgramTex, -50, limites, elementosDecorativos, 2, luces, rutaTexturasSkyBox, rutaTexturaSuelo);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 5;
	elementosDecorativos[ID_PEDRA2] = 2;
	elementosDecorativos[ID_PEDRA3] = 10;
	elementosDecorativos[ID_ARBORE1] = 20;
	elementosDecorativos[ID_HERBA] = 20;

	std::vector<Luz*> luzDireccional3;
	luzDireccional3.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.6f), glm::vec3(1.0f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional3;

	rutaTexturaSuelo = "recursos/texturas/sand2.jpg";

	mundo = new Mundo(personaxePrincipal, shaderProgram, shaderProgramTex, -100, limites, elementosDecorativos, 3, luces, rutaTexturasSkyBox, rutaTexturaSuelo);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 11;
	elementosDecorativos[ID_PEDRA2] = 5;
	elementosDecorativos[ID_PEDRA3] = 15;
	elementosDecorativos[ID_ARBORE1] = 15;
	elementosDecorativos[ID_HERBA] = 40;

	std::vector<Luz*> luzDireccional4;
	luzDireccional4.push_back(new Luz(glm::vec3(0, -3, 5), glm::vec3(0), glm::vec3(0.3f), glm::vec3(0.1f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional4;
	std::vector<Luz*> luzFocal;
	luzFocal.push_back(new Luz(glm::vec3(1.0f, 0.8f, 1.2f), normalize(glm::vec3(0, -0.35f, 1.0f)), glm::vec3(1.0f, 1.0f, 0.2f), glm::vec3(1.0f, 1.0f, 0.2f), 0.89f, 0.84f));
	luzFocal.push_back(new Luz(glm::vec3(-1.0f, 0.8f, 1.2f), normalize(glm::vec3(0, -0.35f, 1.0f)), glm::vec3(1.0f, 1.0f, 0.2f), glm::vec3(1.0f, 1.0f, 0.2f), 0.89f, 0.84f));
	luces[LUZ_FOCAL] = luzFocal;

	rutaTexturaSuelo = "recursos/texturas/hierba.bmp";
	std::string rutaTexturasSkyBox_Nocturno[4];
	rutaTexturasSkyBox_Nocturno[0] = "recursos/texturas/stars.jpg";
	rutaTexturasSkyBox_Nocturno[1] = "recursos/texturas/stars.jpg";
	rutaTexturasSkyBox_Nocturno[2] = "recursos/texturas/stars.jpg";
	rutaTexturasSkyBox_Nocturno[3] = "recursos/texturas/stars.jpg";

	mundo = new Mundo(personaxePrincipal, shaderProgram, shaderProgramTex, -150, limites, elementosDecorativos, 4, luces, rutaTexturasSkyBox_Nocturno, rutaTexturaSuelo);
	mundos.push_back(mundo);

	idMundoActual = 0;
	mundos[0]->iniciarMundo(Camara::SCR_WIDTH, Camara::SCR_HEIGHT);
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
	// Collemos as proporcions da camara do anterior mundo
	float width =  mundos[idMundoActual]->camara->width;
	float height = mundos[idMundoActual]->camara->height;

	if (idMundoActual != 3) {
		idMundoActual++;
	}
	else {
		idMundoActual = 0;
		std::cout << "VOLVEMOS MUNDO1\n";
	}
	
	mundos[idMundoActual]->iniciarMundo(width, height);
}

void Partida::finalizarMundo() {

}


