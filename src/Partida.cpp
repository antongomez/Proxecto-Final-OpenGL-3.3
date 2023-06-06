#include "encabezados/Partida.hpp"
#include "encabezados/definicions.h"
#include "encabezados/AudioHelper.hpp"
#include "encabezados/TextHelper.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <glad.h>

#include <iostream>
#include <utility>

Partida::Partida(GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramMiniMapa) {
	this->shaderProgram = shaderProgram;
	this->shaderProgramTex = shaderProgramTex;
	this->shaderProgramMiniMapa = shaderProgramMiniMapa;
	iniciarPartida();
}

void Partida::iniciarPartida() {
	// Non determinamos a posicion do personaxe principal, pero si o seu escalado. A posicion variara cos mundos pero non a escala
	std::vector<std::string> rutasPersonaxe;
	rutasPersonaxe.push_back("recursos/modelos/Chieftain_tanque.obj");
	rutasPersonaxe.push_back("recursos/modelos/BMP2_hull.obj");
	rutasPersonaxe.push_back("recursos/modelos/Leopard_2A4.obj");
	std::vector<std::string> nomesTanques;
	nomesTanques.push_back("CHIEFTAIN");
	nomesTanques.push_back("BMP2");
	nomesTanques.push_back("LEOPARD");
	std::vector<std::pair<float, float>> dimensionsTanques;
	dimensionsTanques.push_back(std::pair<float, float>(3.58, 1.68));
	dimensionsTanques.push_back(std::pair<float, float>(3.54, 1.71));
	dimensionsTanques.push_back(std::pair<float, float>(3.73, 1.75));

	std::vector<std::pair<float, float>> posicionTorreta;
	posicionTorreta.push_back(std::pair<float, float>(1.2, 2.8));
	posicionTorreta.push_back(std::pair<float, float>(1.2, 0.8));
	posicionTorreta.push_back(std::pair<float, float>(1.2, 2.5));

	float limites[] = { -37.5f, 37.5f };

	this->personaxePrincipal = new PersonaxePrincipal(glm::vec3(0, 0, 0), glm::vec3(1.0f), 0, shaderProgram, FIGURA_CARGADA, rutasPersonaxe, dimensionsTanques, nomesTanques, limites, posicionTorreta);

	// Creamos a pantalla de carga inicial
	float limitesPI[] = { 0, 0 };

	std::map<int, std::vector<Luz*>> luces;

	std::vector<Luz*> luzFocal0;
	luzFocal0.push_back(new Luz(glm::vec3(-2.0f, 5.0f, 0), normalize(glm::vec3(0.5f, -5.0f, 0)), glm::vec3(1.0f, 0.8f, 1.0f), glm::vec3(1.0f, 0.8f, 1.0f), 0.89f, 0.84f, false));
	luzFocal0.push_back(new Luz(glm::vec3(2.0f, 5.0f, 0), normalize(glm::vec3(-0.5f, -5.0f, 0)), glm::vec3(1.0f, 0.8f, 1.0f), glm::vec3(1.0f, 0.8f, 1.0f), 0.89f, 0.84f, false));
	luzFocal0.push_back(new Luz(glm::vec3(0.0f, 5.0f, 2.0f), normalize(glm::vec3(0, -5.0f, -0.5f)), glm::vec3(1.0f, 0.8f, 1.0f), glm::vec3(1.0f, 0.8f, 1.0f), 0.89f, 0.84f, false));
	luzFocal0.push_back(new Luz(glm::vec3(0.0f, 5.0f, -2.0f), normalize(glm::vec3(0, -5.0f, 0.5f)), glm::vec3(1.0f, 0.8f, 1.0f), glm::vec3(1.0f, 0.8f, 1.0f), 0.89f, 0.84f, false));
	luces[LUZ_FOCAL] = luzFocal0;

	std::vector<Luz*> luzPosicional0;
	luzPosicional0.push_back(new Luz(glm::vec3(0, 4, 0), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0f, 0.14f, 0.07f));
	luces[LUZ_POSICIONAL] = luzPosicional0;

	std::string rutaTexturaSuelo = "recursos/texturas/textura-suelo-pantalla-inicial.jpg";
	std::string rutaTexturaMetalica = "recursos/texturas/textura-parte-abaixo.jpg";

	PantallaInicial* pi = new PantallaInicial(personaxePrincipal, shaderProgram, shaderProgramTex, shaderProgramMiniMapa,
		limitesPI, luces, rutaTexturaSuelo, rutaTexturaMetalica);
	mundos.push_back(pi);

	// Creamos os mundos

	std::map<int, int> elementosDecorativos;

	elementosDecorativos[ID_PEDRA1] = 30;
	elementosDecorativos[ID_PEDRA2] = 20;
	elementosDecorativos[ID_PEDRA3] = 50;
	elementosDecorativos[ID_ARBORE1] = 20;
	elementosDecorativos[ID_ARBORE2] = 3;
	elementosDecorativos[ID_ARBORE3] = 0;
	elementosDecorativos[ID_HERBA] = 150;

	std::vector<Luz*> luzDireccional1;
	luzDireccional1.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.7f), glm::vec3(1.0f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional1;

	// Quitamos as luces focais do anterior mundo
	luces.erase(LUZ_FOCAL);
	luces.erase(LUZ_POSICIONAL);

	rutaTexturaSuelo = "recursos/texturas/hierba.bmp";
	std::string rutaTexturaMuro = "recursos/texturas/paredeMundo1.jpg";
	std::string rutaTexturasSkyBox[4];
	rutaTexturasSkyBox[0] = "recursos/texturas/left.jpg";
	rutaTexturasSkyBox[1] = "recursos/texturas/right.jpg";
	rutaTexturasSkyBox[2] = "recursos/texturas/front.jpg";
	rutaTexturasSkyBox[3] = "recursos/texturas/back.jpg";

	Mundo* mundo = new Mundo(personaxePrincipal, shaderProgram, shaderProgramTex, shaderProgramMiniMapa,
		0, limites, elementosDecorativos, 1, luces, rutaTexturasSkyBox, rutaTexturaSuelo, rutaTexturaMuro);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 100;
	elementosDecorativos[ID_PEDRA2] = 65;
	elementosDecorativos[ID_PEDRA3] = 80;
	elementosDecorativos[ID_ARBORE1] = 0;
	elementosDecorativos[ID_ARBORE2] = 0;
	elementosDecorativos[ID_ARBORE3] = 20;
	elementosDecorativos[ID_HERBA] = 0;

	std::vector<Luz*> luzDireccional2;
	luzDireccional2.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.8f), glm::vec3(1.0f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional2;

	rutaTexturaSuelo = "recursos/texturas/area.jpg";
	rutaTexturaMuro = "recursos/texturas/paredeMundo2.jpg";
	std::string rutaTexturasSkyBox_Deserto[4];
	rutaTexturasSkyBox_Deserto[0] = "recursos/texturas/leftDesert.jpg";
	rutaTexturasSkyBox_Deserto[1] = "recursos/texturas/rightDesert.jpg";
	rutaTexturasSkyBox_Deserto[2] = "recursos/texturas/frontDesert.jpg";
	rutaTexturasSkyBox_Deserto[3] = "recursos/texturas/backDesert.jpg";

	mundo = new Mundo(personaxePrincipal, shaderProgram, shaderProgramTex, shaderProgramMiniMapa,
		-50, limites, elementosDecorativos, 2, luces, rutaTexturasSkyBox_Deserto, rutaTexturaSuelo, rutaTexturaMuro);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 15;
	elementosDecorativos[ID_PEDRA2] = 20;
	elementosDecorativos[ID_PEDRA3] = 30;
	elementosDecorativos[ID_ARBORE1] = 50;
	elementosDecorativos[ID_ARBORE2] = 25;
	elementosDecorativos[ID_ARBORE3] = 0;
	elementosDecorativos[ID_HERBA] = 200;

	std::vector<Luz*> luzDireccional3;
	luzDireccional3.push_back(new Luz(glm::vec3(0, -5, 3), glm::vec3(0.6f), glm::vec3(1.0f), glm::vec3(1.0f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional3;

	rutaTexturaSuelo = "recursos/texturas/hierba.bmp";
	rutaTexturaMuro = "recursos/texturas/paredeMundo1.jpg";

	mundo = new Mundo(personaxePrincipal, shaderProgram, shaderProgramTex, shaderProgramMiniMapa,
		-100, limites, elementosDecorativos, 3, luces, rutaTexturasSkyBox, rutaTexturaSuelo, rutaTexturaMuro);
	mundos.push_back(mundo);

	elementosDecorativos[ID_PEDRA1] = 30;
	elementosDecorativos[ID_PEDRA2] = 30;
	elementosDecorativos[ID_PEDRA3] = 35;
	elementosDecorativos[ID_ARBORE1] = 35;
	elementosDecorativos[ID_ARBORE2] = 2;
	elementosDecorativos[ID_ARBORE3] = 0;
	elementosDecorativos[ID_HERBA] = 120;

	std::vector<Luz*> luzDireccional4;
	luzDireccional4.push_back(new Luz(glm::vec3(0, -3, 5), glm::vec3(0), glm::vec3(0.3f), glm::vec3(0.1f)));
	luces[LUZ_DIRECCIONAL] = luzDireccional4;
	std::vector<Luz*> luzFocal;
	luzFocal.push_back(new Luz(glm::vec3(1.0f, 0.8f, 1.2f), normalize(glm::vec3(0, -0.35f, 1.0f)), glm::vec3(1.0f, 1.0f, 0.2f), glm::vec3(1.0f, 1.0f, 0.2f), 0.89f, 0.84f, true));
	luzFocal.push_back(new Luz(glm::vec3(-1.0f, 0.8f, 1.2f), normalize(glm::vec3(0, -0.35f, 1.0f)), glm::vec3(1.0f, 1.0f, 0.2f), glm::vec3(1.0f, 1.0f, 0.2f), 0.89f, 0.84f, true));
	luces[LUZ_FOCAL] = luzFocal;

	rutaTexturaSuelo = "recursos/texturas/hierba.bmp";
	rutaTexturaMuro = "recursos/texturas/paredeMundo4.jpg";
	std::string rutaTexturasSkyBox_Nocturno[4];
	rutaTexturasSkyBox_Nocturno[0] = "recursos/texturas/stars.jpg";
	rutaTexturasSkyBox_Nocturno[1] = "recursos/texturas/stars.jpg";
	rutaTexturasSkyBox_Nocturno[2] = "recursos/texturas/stars.jpg";
	rutaTexturasSkyBox_Nocturno[3] = "recursos/texturas/stars.jpg";

	mundo = new Mundo(personaxePrincipal, shaderProgram, shaderProgramTex, shaderProgramMiniMapa,
		-150, limites, elementosDecorativos, 4, luces, rutaTexturasSkyBox_Nocturno, rutaTexturaSuelo, rutaTexturaMuro);
	mundos.push_back(mundo);

	idMundoActual = 0;
	mundos[0]->iniciar(Camara::SCR_WIDTH, Camara::SCR_HEIGHT);

	iniciarMusica();

	this->tempoPartida = 0;
}

void Partida::iniciarMusica() {
	AudioHelper::GetInstance()->reproducirMelodiaMundo(idMundoActual);
}

void Partida::moverObxectos(float tempoTranscurrido) {

	mundos[idMundoActual]->moverObxectos(tempoTranscurrido);

	// Actualizamos o tempo da partida
	double tempoActual = glfwGetTime();
	tempoPartida = tempoActual - tempoInicioPartida;

	mundos[idMundoActual]->renderizarEscena(tempoPartida);

	// Comprobamos se xa matamos a todos os inimigos deste mundo
	if (mundos[idMundoActual]->mundoCompletado()) {

		if (idMundoActual == 0) {
			seguinteMundo();
		}
		else {

			if (!mundos[idMundoActual]->musica_reproducida) {
				AudioHelper* ah = AudioHelper::GetInstance();
				ah->reproducirSon(SON_NIVEL_COMPLETADO);
				ah->pausarMelodiaMundo(idMundoActual);
				mundos[idMundoActual]->musica_reproducida = true;
			}

			if (mundos[idMundoActual]->instantes_pausa >= INSTANTES_PAUSA_NIVEL_COMPLETADO) {
				seguinteMundo();
			}
			else {
				mundos[idMundoActual]->instantes_pausa++;
			}
		}
	}
}

void Partida::reescalarVenta(GLFWwindow* window, int width, int height) {
	TextHelper::GetInstance()->cambiarViewport(width, height);
	mundos[idMundoActual]->reescalarVenta(window, width, height);
}

void Partida::eventoTeclado(GLFWwindow* window, int tecla, int accion) {

	// Tecla ENTER
	if (tecla == 257 && accion == GLFW_RELEASE) {
		AudioHelper* ah = AudioHelper::GetInstance();
		ah->pausarMelodiaMundo(idMundoActual);
		if (idMundoActual == 0) {
			ah->reproducirSon(SON_XOGO_ARRANQUE);
			mundos[0]->tempoPulsoEnter = glfwGetTime();
			if (personaxePrincipal->angulo <= ANGULO_PAUSA_FIN_PANTALLA_INICIAL) {
				mundos[0]->anguloPulsoEnter = personaxePrincipal->angulo;
			}
			else {
				mundos[0]->anguloPulsoEnter = personaxePrincipal->angulo - 2.0f*PI;
			}
			
		}
		else {
			seguinteMundo();
		}
	}

	mundos[idMundoActual]->eventoTeclado(window, tecla, accion);
}

void Partida::seguinteMundo() {
	mundos[idMundoActual]->finalizarMundo();
	// Collemos as proporcions da camara do anterior mundo
	float width = mundos[idMundoActual]->camara->width;
	float height = mundos[idMundoActual]->camara->height;

	// Rexistramos o inicio da partida
	if (idMundoActual == 0) {
		tempoInicioPartida = glfwGetTime();
	}

	if (idMundoActual != (mundos.size() - 1)) {
		idMundoActual++;
	}
	else {
		idMundoActual = 0;
	}
	AudioHelper::GetInstance()->reproducirMelodiaMundo(idMundoActual);
	mundos[idMundoActual]->iniciar(width, height);
}


