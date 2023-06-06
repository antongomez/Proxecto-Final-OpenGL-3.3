#include "encabezados/Mundo.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <random>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "encabezados/PantallaInicial.hpp"
#include "encabezados/AudioHelper.hpp"
#include "encabezados/TextHelper.hpp"

Mundo::Mundo(PersonaxePrincipal* personaxePrincipal, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramBasico,
	float alturaMundo, float* limites,
	std::map<int, int> elementosDecorativos, int nivelMundo, std::map<int, std::vector<Luz*>> luces,
	std::string rutaTexturasSkyBox[],
	std::string rutaTexturaSuelo, std::string rutaTexturaMuro) : PantallaInicial(personaxePrincipal, shaderProgram, shaderProgramTex, shaderProgramBasico, luces)
{
	this->nivelMundo = nivelMundo;
	this->pausa = false;
	this->minimapa = true;

	xerarSuelo(alturaMundo, limites, rutaTexturaSuelo, rutaTexturaMuro);
	xerarSkyBox(alturaMundo, limites, rutaTexturasSkyBox);
	xerarElementosDecorativos(elementosDecorativos);
	xerarInimigos(nivelMundo);
}

void Mundo::iniciar(float width, float height) {
	this->camara = new Camara(20.0f, PI / 2.0f, PI / 4.0f, width, height, MODO_CAMARA_TERCEIRA_PERSOA);

	// colocamos ao personaxe principal sobre o chan no centro do mesmo
	personaxePrincipal->posicion = glm::vec3(suelo->posicion.x, suelo->posicion.y, suelo->posicion.z);
	personaxePrincipal->angulo = 0;

	this->camaraSecundaria = new Camara(10.0f, PI, PI / 2.0f - UNIDADE_GRAO_EN_RADIANS, width, height, MODO_CAMARA_VISTA_XERAL);

	inimigosRestantes = inimigos.size();
	tempoInicioMundo = glfwGetTime();

	for (int i = 0; i < 4; i++) {
		pitidos[i] = false;
	}

	this->win = false;
	this->defeat = false;
}

void Mundo::xerarSkyBox(float alturaMundo, float* limites, std::string rutaTexturas[]) {
	this->skyBox = new SkyBox(limites[1], alturaMundo, shaderProgramTex, FIGURA_CADRADO, rutaTexturas);
}

void Mundo::xerarSuelo(float alturaMundo, float* limites, std::string rutaTextura, std::string rutaTexturaMuro) {
	this->suelo = new Suelo(glm::vec3(0, alturaMundo, 0), ESCALA_SUELO, limites, shaderProgramTex, FIGURA_CADRADO, rutaTextura, rutaTexturaMuro);
}

void Mundo::xerarElementosDecorativos(std::map<int, int> elementosDecorativos) {

	std::map<int, int>::iterator iterador;

	// Recorrer el vector utilizando el iterador
	for (iterador = elementosDecorativos.begin(); iterador != elementosDecorativos.end(); ++iterador) {
		int idElemento = iterador->first;

		std::string rutaOBJ;
		bool hittable = false;
		switch (idElemento) {
		case ID_PEDRA1:
			rutaOBJ = "recursos/modelos/pedra1.obj";
			break;
		case ID_PEDRA2:
			rutaOBJ = "recursos/modelos/pedra2.obj";
			break;
		case ID_PEDRA3:
			rutaOBJ = "recursos/modelos/pedra3.obj";
			break;
		case ID_ARBORE1:
			rutaOBJ = "recursos/modelos/arbore1.obj";
			hittable = true;
			break;
		case ID_ARBORE2:
			rutaOBJ = "recursos/modelos/arbore2.obj";
			hittable = true;
			break;
		case ID_ARBORE3:
			rutaOBJ = "recursos/modelos/arbore3.obj";
			hittable = true;
			break;
		case ID_HERBA:
			rutaOBJ = "recursos/modelos/Herba.obj";
			break;
		}

		int numElementos = iterador->second;

		std::random_device rd;
		std::mt19937 generator(rd());

		// Facemos que os obxectos aparezan xirados cun angulo aleatorio
		std::uniform_real_distribution<float> distribucionAngulo(0, 2.0f * PI);

		// Definir una distribución para generar números reales en un rango
		std::uniform_real_distribution<float> distribucionX(0, suelo->limites[1]);
		std::uniform_real_distribution<float> distribucionZ(0, suelo->limites[1]);

		std::uniform_real_distribution<float> distribucionZ_2(6, suelo->limites[1]);

		std::uniform_int_distribution<int> distribucionAux(0, 1);

		for (int i = 0; i < numElementos; i++) {
			int aux1 = (distribucionAux(generator) == 0) ? -1 : 1;
			float posX = (float)aux1 * distribucionX(generator);
			int aux2 = (distribucionAux(generator) == 0) ? -1 : 1;

			float posZ;
			if (posX < 6 && posX > -6) {
				posZ = (float)aux2 * distribucionZ_2(generator);
			}
			else {
				posZ = (float)aux2 * distribucionZ(generator);
			}

			glm::vec3 posicion(posX, suelo->posicion.y, posZ);
			glm::vec3 escala(1.0f);

			Obxecto* obxecto = new Obxecto(posicion, escala, distribucionAngulo(generator), shaderProgram, rutaOBJ, hittable);
			obxectosDecorativos.push_back(obxecto);
		}
	}
}

void Mundo::xerarInimigos(int nivelInimigos) {
	//int numEnemigos = nivelInimigos * 10;
	int numEnemigos = 7 + nivelInimigos * 3;

	std::random_device rd;
	std::mt19937 generator(rd());

	// Definir una distribución para generar números reales en un rango
	std::uniform_real_distribution<float> distribucionRadio(8, suelo->limites[1]);
	std::uniform_real_distribution<float> distribucionAngulo(0, 2 * PI);

	for (int i = 0; i < numEnemigos; i++) {
		float radio = distribucionRadio(generator);
		float angulo = distribucionAngulo(generator);

		glm::vec3 posicion(radio * sin(angulo), suelo->posicion.y, radio * cos(angulo));
		glm::vec3 escala(1.0f);

		Enemigo* enemigo = new Enemigo(posicion, escala, 0, shaderProgram, FIGURA_CUBO, nivelInimigos, personaxePrincipal);

		inimigos.push_back(enemigo);
	}
}

void Mundo::recolocarInimigos() {

	std::random_device rd;
	std::mt19937 generator(rd());

	// Definir una distribución para generar números reales en un rango
	std::uniform_real_distribution<float> distribucionRadio(8, suelo->limites[1]);
	std::uniform_real_distribution<float> distribucionAngulo(0, 2 * PI);

	for (const auto& inimigo : inimigos) {
		float radio = distribucionRadio(generator);
		float angulo = distribucionAngulo(generator);

		glm::vec3 posicion(radio * sin(angulo), suelo->posicion.y, radio * cos(angulo));

		inimigo->posicion = posicion;
	}
}

void Mundo::finalizarMundo() {
	// Recolocamos aleatoriamente os inimigos e marcamolos a todos como vivos
	std::random_device rd;
	std::mt19937 generator(rd());

	// Definir una distribución para generar números reales en un rango
	std::uniform_real_distribution<float> distribucionRadio(8, suelo->limites[1]);
	std::uniform_real_distribution<float> distribucionAngulo(0, 2 * PI);

	for (const auto& inimigo : inimigos) {
		float radio = distribucionRadio(generator);
		float angulo = distribucionAngulo(generator);

		glm::vec3 posicion(radio * sin(angulo), suelo->posicion.y, radio * cos(angulo));

		inimigo->posicion = posicion;
		inimigo->estado = 1;
		inimigo->instantes_animacion = 0;
	}

	musica_reproducida = false;
	instantes_pausa = 0;
}

void Mundo::establecerCamara() {
	camara->establecerCamara(personaxePrincipal);
	// Actualizamos a matriz de proxeccion
	camara->actualizarMatrizProxeccion();
}

void Mundo::moverObxectos(float tempoTranscurrido) {
	if (!pausa && !defeat) {
		// Temos o tempo que se tarda en pasar o mundo
		tempoRestanteEmpezar = SEGUNDOS_PAUSA_INICIO_NIVEL - glfwGetTime() + tempoInicioMundo;

		if (tempoRestanteEmpezar < 0) {

			personaxePrincipal->moverPersonaxe(tempoTranscurrido, obxectosDecorativos);
			for (int i = 0; i < inimigos.size(); i++) {
				inimigos[i]->moverEnemigo(tempoTranscurrido);
			}

			// Comprobamos as posibles colisions
			colisionsBalas();
			colisionsTanqueInimigo();
		}
	}
}

bool Mundo::mundoCompletado() {
	bool completado = true;
	for (int i = 0; i < inimigos.size(); i++) {
		if (inimigos[i]->estado == 1) {
			completado = false;
		}
	}
	return completado;
}

void Mundo::colisionsBalas() {

	bool sair = false;

	for (auto iterBala = personaxePrincipal->balas.begin(); iterBala != personaxePrincipal->balas.end(); iterBala++) {
		Bala* bala = *iterBala;
		for (auto inimigo : inimigos) {
			if (glm::distance(bala->posicion, inimigo->posicion) <= DIST_COLISION_BALA) {
				if (inimigo->estado == 1) {
					inimigo->estado = 2;
					AudioHelper::GetInstance()->reproducirSon(SON_INIMIGO_MATADO, 0.25f);
					personaxePrincipal->balas.erase(iterBala);
					inimigosRestantes--;
					sair = true;
					break;
				}
			}
		}
		if (sair) break;

	}
}

void Mundo::colisionsTanqueInimigo() {
	// Matriz que leva calquera punto ao local space do tanque, para simplificar a comprobacion da colision
	glm::mat4 toLocalSpace = glm::mat4();
	toLocalSpace = glm::rotate(toLocalSpace, personaxePrincipal->angulo, glm::vec3(0.0, -1.0, 0.0));
	toLocalSpace = glm::translate(toLocalSpace, -personaxePrincipal->posicion);

	for (int i = 0; i < inimigos.size(); i++) {
		if (inimigos[i]->estado == 1) {
			glm::vec3 pos_local = glm::vec3(toLocalSpace * glm::vec4(inimigos[i]->posicion, 1.0f));
			if (pos_local.x >= -(personaxePrincipal->ancho / 2 + RADIO_ENEMIGO) &&
				pos_local.x <= personaxePrincipal->ancho / 2 + RADIO_ENEMIGO &&
				pos_local.z >= -(personaxePrincipal->largo / 2 + RADIO_ENEMIGO) &&
				pos_local.z <= personaxePrincipal->largo / 2 + RADIO_ENEMIGO) {

				std::cout << pos_local.x << std::endl;
				std::cout << pos_local.x << std::endl;

				// Funcion que gestiona la colision
				ataqueProducido();
			}
		}
	}
}

void Mundo::ataqueProducido() {
	personaxePrincipal->vidas--;
	AudioHelper* ah = AudioHelper::GetInstance();



	ah->reproducirSon(SON_NIVEL_FALLIDO, 0.25f);
	ah->pausarMelodiaMundo(nivelMundo);

	if (personaxePrincipal->vidas == 0) {
		ah->reproducirMelodiaDerrota();
		defeat = true;
	}
	else {
		pausa = true;
	}


}

void Mundo::renderizarMiniMapa() {
	float ancho = 400;
	float alto = ancho * PROPORCION_MINIMAPA;
	glViewport(camara->width - ancho - 20, camara->height - alto - 20, ancho, alto);

	// Utilizamos o shader para os obxectos que non tenhen texturas
	glUseProgram(shaderProgramBasico);

	camaraSecundaria->establecerCamara(personaxePrincipal);
	camaraSecundaria->actualizarMatrizProxeccionOrtho(35.0f);
	camaraSecundaria->actualizarMatricesShader(shaderProgram);

	// O obxecto pintamolo doutra cor
	unsigned int loc_cor = glGetUniformLocation(shaderProgramBasico, "cor");
	glUniform1i(loc_cor, 1);

	unsigned int loc_color = glGetUniformLocation(shaderProgramBasico, "color");

	personaxePrincipal->renderizarObxecto();

	for (int i = 0; i < inimigos.size();i++) {
		if (inimigos[i]->estado == 1) {
			inimigos[i]->renderizarObxecto();
		}
	}

	glm::vec3 corChan;
	glm::vec3 corMuro;
	if (nivelMundo == 1 || nivelMundo == 3) {
		corChan = glm::vec3(0, 0.3f, 0);
		corMuro = glm::vec3(0.5f, 0.5f, 0.5f);
	}
	else if (nivelMundo == 2) {
		corChan = glm::vec3(0.75f, 0.64f, 0.40f);
		corMuro = glm::vec3(0.5f, 0.4f, 0.3f);
	}
	else {
		corChan = glm::vec3(0, 0.3f, 0);
		corMuro = glm::vec3(1.0f, 0.7f, 0.4f);
	}

	glUniform3fv(loc_color, 1, value_ptr(corChan));
	suelo->renderizarSuelo();

	glUniform3fv(loc_color, 1, value_ptr(corMuro));
	suelo->renderizarParteArribaMuro();

}

void Mundo::renderizarEscena(float tempoTranscurrido) {

	glViewport(0, 0, camara->width, camara->height);

	// Utilizamos o shader para os obxectos que non tenhen texturas
	glUseProgram(shaderProgram);

	establecerCamara();
	// Establecemos as matrices de view e projection no shader
	camara->actualizarMatricesShader(shaderProgram);
	// Establecemos a posicion da camara no shader
	unsigned int viewPos = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3fv(viewPos, 1, glm::value_ptr(camara->posicionCamara));
	// Luces no shader
	establecerLucesShader(shaderProgram);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// La variable alpha la usamos para la animacion de la muerte de los enemigos
	unsigned int alphaLoc = glGetUniformLocation(shaderProgram, "alpha");
	glUniform1f(alphaLoc, 1.0f);

	personaxePrincipal->renderizarObxecto();
	personaxePrincipal->renderizarBalas();

	for (int i = 0; i < obxectosDecorativos.size(); i++) {
		obxectosDecorativos[i]->renderizarObxecto();
	}

	for (int i = 0; i < inimigos.size();i++) {
		// Se esta vivo, renderizamolo sen mais
		if (inimigos[i]->estado == 1) {
			inimigos[i]->renderizarObxecto();
		}
		// Se esta semivivo, continuamos coa animacion
		else if (inimigos[i]->estado == 2) {
			// Calculamos o valor do canal alpha para este instante
			float alpha = (INSTANTES_TOTAL_ANIMACION - inimigos[i]->instantes_animacion / 2) / (float)INSTANTES_TOTAL_ANIMACION;

			glUniform1f(alphaLoc, alpha);
			inimigos[i]->renderizarObxecto();
			// Devolvemos el canal alpha a su valor por defecto
			glUniform1f(alphaLoc, 1.0f);


			if (inimigos[i]->instantes_animacion >= INSTANTES_TOTAL_ANIMACION) {
				// Se xa rematou a animacion, pasa a estado "morto"
				inimigos[i]->estado = 0;
			}
			inimigos[i]->instantes_animacion++;
		}
	}

	glUseProgram(shaderProgramTex);
	// Establecemos as matrices de view e projection no shader
	camara->actualizarMatricesShader(shaderProgram);
	// Establecemos as luces no shader
	establecerLucesShader(shaderProgramTex);

	// Variable do shader para determinar se estamos iluminando o skyBox ou non
	unsigned int loc_skyBox = glGetUniformLocation(shaderProgramTex, "skyBox");
	glUniform1i(loc_skyBox, 0);

	suelo->renderizarSuelo();
	suelo->renderizarMuro();

	// Actuvamos a variable do shader para iluminar o skyBox
	glUniform1i(loc_skyBox, 1);

	skyBox->renderizarSkyBox();

	TextHelper* t = TextHelper::GetInstance();
	t->cambiarViewport(camara->width, camara->height);
	std::stringstream ss;
	ss << "Vidas: " << personaxePrincipal->vidas << "\nInimigos: " << std::to_string(inimigosRestantes) << "\n" << std::fixed << std::setprecision(3) << tempoTranscurrido;
	t->setTexto(ss.str());
	t->escribir(20, 20, 2.0f, 0, 0);

	double tempoRestanteEmpezar = SEGUNDOS_PAUSA_INICIO_NIVEL - glfwGetTime() + tempoInicioMundo;
	if (tempoRestanteEmpezar > 0 && tempoRestanteEmpezar <= 3) {
		std::stringstream st;
		st << std::fixed << std::setprecision(0) << std::ceil(tempoRestanteEmpezar);
		t->setTexto(st.str());
		t->escribir(camara->width * 0.5f, camara->height * 0.5f, 4.0f, 1, 1);
	}
	emitirPitidos(tempoRestanteEmpezar);

	if (pausa) {
		TextHelper* t = TextHelper::GetInstance();
		t->cambiarViewport(camara->width, camara->height);
		t->setTexto("Os trolls devoraronte!");
		t->escribir(camara->width / 2.0f, camara->height / 2.0f - 20, 2.0f, 1, 1);
		t->setTexto("Presiona ENTER para reitentar o nivel");
		t->escribir(camara->width / 2.0f, camara->height / 2.0f + 20, 1.5f, 1, 1);
	}
	else if (mundoCompletado() && !win) {
		TextHelper* t = TextHelper::GetInstance();
		t->cambiarViewport(camara->width, camara->height);
		t->setTexto("Nivel completado!");
		t->escribir(camara->width / 2.0f, camara->height / 2.0f, 2.0f, 1, 1);
	}
	else if (win) {
		TextHelper* t = TextHelper::GetInstance();
		t->cambiarViewport(camara->width, camara->height);
		t->setTexto("XOGO COMPLETADO");
		t->escribir(camara->width / 2.0f, camara->height / 2.0f - 50, 4.0f, 1, 1);
		std::stringstream sw;
		sw << "Tempo empregado: " << std::fixed << std::setprecision(3) << tempoTranscurrido;
		t->setTexto(sw.str());
		t->escribir(camara->width / 2.0f, camara->height / 2.0f + 10, 3.0f, 1, 1);
		t->setTexto("Presiona ENTRER para reiniciar o xogo");
		t->escribir(camara->width / 2.0f, camara->height / 2.0f + 60, 2.0f, 1, 1);
	}
	else if (defeat) {
		TextHelper* t = TextHelper::GetInstance();
		t->cambiarViewport(camara->width, camara->height);
		t->setTexto("Derrota!");
		t->escribir(camara->width / 2.0f, camara->height / 2.0f - 30, 4.0f, 1, 1);
		t->setTexto("Presiona ENTER para reiniciar o xogo");
		t->escribir(camara->width / 2.0f, camara->height / 2.0f + 20, 1.5f, 1, 1);
	}

	if (minimapa) {
		renderizarMiniMapa();
	}


}

void Mundo::emitirPitidos(double tempoRestante) {

	if (tempoRestante > 2 && tempoRestante <= 3 && !pitidos[3]) {
		AudioHelper::GetInstance()->reproducirSon(SON_BEEP_BAIXO, 0.5f);
		pitidos[3] = true;
	}
	else if (tempoRestante > 1 && tempoRestante <= 2 && !pitidos[2]) {
		AudioHelper::GetInstance()->reproducirSon(SON_BEEP_BAIXO, 0.5f);
		pitidos[2] = true;
	}
	else if (tempoRestante > 0 && tempoRestante <= 1 && !pitidos[1]) {
		AudioHelper::GetInstance()->reproducirSon(SON_BEEP_BAIXO, 0.5f);
		pitidos[1] = true;
	}
	else if (tempoRestante <= 0.25 && !pitidos[0]) {
		AudioHelper::GetInstance()->reproducirSon(SON_BEEP_ALTO);
		pitidos[0] = true;
	}

}

// Funcion que xestiona os controis. Deste xeito cada mundo poderia cambiar, por exemplo, a velocidade de movemento do personaxe
void Mundo::eventoTeclado(GLFWwindow* window, int tecla, int accion) {

	// --------------- personaxe principal MOVEMENTOS -------------------------- //
	// 
	// Tecla d: xiro do personaxe a dereita
	if (tecla == 68) {
		if (accion == GLFW_PRESS) {
			personaxePrincipal->xirar_dereita = true;
			personaxePrincipal->xirar_esquerda = false;
		}

		if (accion == GLFW_RELEASE) {
			personaxePrincipal->xirar_dereita = false;
		}
	}

	// Tecla a: xiro do personaxe a esquerda
	if (tecla == 65) {
		if (accion == GLFW_PRESS) {
			personaxePrincipal->xirar_esquerda = true;
			personaxePrincipal->xirar_dereita = false;
		}

		if (accion == GLFW_RELEASE) {
			personaxePrincipal->xirar_esquerda = false;
		}
	}

	// Tecla w: desprazarse cara diante
	if (tecla == 87) {

		if (accion == GLFW_PRESS) {
			personaxePrincipal->moverse = true;
			personaxePrincipal->marcha_atras = false;
		}

		if (accion == GLFW_RELEASE) {
			personaxePrincipal->moverse = false;
		}
	}

	// Tecla s: desprazarse cara atras
	if (tecla == 83) {

		if (accion == GLFW_PRESS) {
			personaxePrincipal->marcha_atras = true;
			personaxePrincipal->moverse = false;
		}

		if (accion == GLFW_RELEASE) {
			personaxePrincipal->marcha_atras = false;
		}
	}

	// --------------- Camara xeral MOVEMENTOS -------------------------- //
	if (camara->modo == MODO_CAMARA_VISTA_XERAL) {
		// Tecla dereita: xiro da camara en vistaXeral a dereita
		if (tecla == 262) {
			moverCamara(XIRO_CAMARA_DEREITA);
		}

		// Tecla esquerda: xiro da camara en vistaXeral a esquerda
		if (tecla == 263) {
			moverCamara(XIRO_CAMARA_ESQUERDA);
		}

		// Tecla arriba: xiro da camara en vistaXeral na vertical cara arriba
		if (tecla == 265) {
			moverCamara(XIRO_CAMARA_ARRIBA);
		}

		// Tecla abaixo: xiro da camara en vistaXeral na vertical cara abaixo
		if (tecla == 264) {
			moverCamara(XIRO_CAMARA_ABAIXO);
		}

		// Tecla +: achegase a camara en vistaXeral
		if (tecla == 93 && accion != GLFW_RELEASE) {
			moverCamara(ACERCAR_CAMARA);
		}

		// Tecla -: afastase a camara en vistaXeral
		if (tecla == 47 && accion != GLFW_RELEASE) {
			moverCamara(AFASTAR_CAMARA);
		}
	}

	// --------------- CAMBIOS camara -------------------------- //
	if (tecla == 49 && accion == GLFW_RELEASE) {
		camara->modo = MODO_CAMARA_PRIMEIRA_PERSOA;
	}
	else if (tecla == 50 && accion == GLFW_RELEASE) {
		camara->modo = MODO_CAMARA_VISTA_XERAL;
	}
	else if (tecla == 51 && accion == GLFW_RELEASE) {
		camara->modo = MODO_CAMARA_TERCEIRA_PERSOA;
	}

	// Disparo
	if (tecla == 32 && accion == GLFW_PRESS) {
		if (tempoRestanteEmpezar <= 0) {
			personaxePrincipal->disparar();
		}

	}

	// Finalizar pausa
	if (tecla == 257 && accion == GLFW_PRESS) {

		if (pausa) {
			finalizarMundo();
			iniciar(camara->width, camara->height);
			AudioHelper::GetInstance()->reproducirMelodiaMundo(nivelMundo);
			pausa = false;
		}
	}

	// Activar/desactivar minimapa
	if (tecla == 77 && accion == GLFW_PRESS) {
		minimapa = !minimapa;
	}
}

void Mundo::moverCamara(int tipoMovemento) {
	switch (tipoMovemento) {
	case XIRO_CAMARA_DEREITA:
		camara->alpha += INCREMENTO_XIRO_CAMARA_XERAL;
		if (camara->alpha >= (float)(2.0 * PI)) {
			camara->alpha -= (float)(2.0 * PI);
		}
		break;
	case XIRO_CAMARA_ESQUERDA:
		camara->alpha -= INCREMENTO_XIRO_CAMARA_XERAL;
		if (camara->alpha <= (float)(-2.0f * PI)) {
			camara->alpha += (float)(2.0f * PI);
		}
		break;
	case XIRO_CAMARA_ARRIBA:
		// Limite superior de 90 grados
		camara->beta = fmin(camara->beta + INCREMENTO_XIRO_CAMARA_XERAL, (float)PI / 2.0f - UNIDADE_GRAO_EN_RADIANS);
		break;
	case XIRO_CAMARA_ABAIXO:
		camara->beta = fmax(camara->beta - INCREMENTO_XIRO_CAMARA_XERAL, (float)-PI / 2.0f + UNIDADE_GRAO_EN_RADIANS);
		break;
	case ACERCAR_CAMARA:
		camara->radio = fmax(camara->radio - INCREMENTO_RADIO_CAMARA_XERAL, MIN_DIST_CAMARA_XERAL);
		break;
	case AFASTAR_CAMARA:
		camara->radio = fmin(camara->radio + INCREMENTO_RADIO_CAMARA_XERAL, MAX_DIST_CAMARA_XERAL);
		break;
	}
}

