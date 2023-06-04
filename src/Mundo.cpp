#include "encabezados/Mundo.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <random>
#include <iostream>

Mundo::Mundo(PersonaxePrincipal* personaxePrincipal, GLuint shaderProgram, GLuint shaderProgramTex, GLuint shaderProgramMiniMapa,
	float alturaMundo, float* limites,
	std::map<int, int> elementosDecorativos, int nivelMundo, std::map<int, std::vector<Luz*>> luces,
	std::string rutaTexturasSkyBox[],
	std::string rutaTexturaSuelo, std::string rutaTexturaMuro)
{

	this->personaxePrincipal = personaxePrincipal;
	this->shaderProgram = shaderProgram;
	this->shaderProgramTex = shaderProgramTex;
	this->shaderProgramMiniMapa = shaderProgramMiniMapa;
	this->nivelMundo = nivelMundo;
	this->luces = luces;

	xerarSuelo(alturaMundo, limites, rutaTexturaSuelo, rutaTexturaMuro);
	xerarSkyBox(alturaMundo, limites, rutaTexturasSkyBox);
	xerarElementosDecorativos(elementosDecorativos);
	xerarInimigos(nivelMundo);
}

void Mundo::iniciarMundo(float width, float height) {
	this->camara = new Camara(20.0f, PI / 2.0f, PI / 4.0f, width, height);

	// colocamos ao personaxe principal sobre o chan no centro do mesmo
	personaxePrincipal->posicion = glm::vec3(suelo->posicion.x, suelo->posicion.y, suelo->posicion.z);
	personaxePrincipal->angulo = 0;

	this->camaraMiniMapa = new Camara(10.0f, PI, PI / 2.0f - UNIDADE_GRAO_EN_RADIANS, width, height);
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
			break;
		case ID_ARBORE2:
			rutaOBJ = "recursos/modelos/arbore2.obj";
			break;
		case ID_ARBORE3:
			rutaOBJ = "recursos/modelos/arbore3.obj";
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

			Obxecto* obxecto = new Obxecto(posicion, escala, distribucionAngulo(generator), shaderProgram, rutaOBJ);
			obxectosDecorativos.push_back(obxecto);
		}
	}
}

void Mundo::xerarInimigos(int nivelInimigos) {
	int numEnemigos = nivelInimigos * 10;

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

		Enemigo* enemigo = new Enemigo(posicion, escala, 0, shaderProgram, FIGURA_CUBO, 1, personaxePrincipal);

		inimigos.push_back(enemigo);
	}
}

void Mundo::establecerCamara() {
	camara->establecerCamara(personaxePrincipal);
	// Actualizamos a matriz de proxeccion
	camara->actualizarMatrizProxeccion();
}

void Mundo::moverObxectos(float tempoTranscurrido) {
	personaxePrincipal->moverPersonaxe(tempoTranscurrido);
	for (int i = 0; i < inimigos.size(); i++) {
		inimigos[i]->moverEnemigo(tempoTranscurrido);
	}
}

void Mundo::establecerLucesShader(GLuint shader) {
	// Iluminacion
	auto iter = luces.find(LUZ_DIRECCIONAL);
	if (iter != luces.end()) {
		// El elemento se encontró en el mapa
		std::vector<Luz*>& vecDir = iter->second;

		// Establecemos a luz direccional
		unsigned int dirLight_direction = glGetUniformLocation(shader, "dirLight.direction");
		glUniform3fv(dirLight_direction, 1, glm::value_ptr(vecDir[0]->direccion));
		unsigned int dirLight_ambient = glGetUniformLocation(shader, "dirLight.ambient");
		glUniform3fv(dirLight_ambient, 1, glm::value_ptr(vecDir[0]->ambiente));
		unsigned int dirLight_diffuse = glGetUniformLocation(shader, "dirLight.diffuse");
		glUniform3fv(dirLight_diffuse, 1, glm::value_ptr(vecDir[0]->difusa));
		unsigned int dirLight_especular = glGetUniformLocation(shader, "dirLight.specular");
		glUniform3fv(dirLight_especular, 1, glm::value_ptr(vecDir[0]->especular));
	}

	iter = luces.find(LUZ_FOCAL);

	if (iter != luces.end()) {
		// El elemento se encontró en el mapa
		std::vector<Luz*>& vecLuzFocal = iter->second;

		// Marcamos no shader que utilizamos luz focal
		unsigned int spot = glGetUniformLocation(shader, "spot");
		glUniform1i(spot, 1);

		for (int i = 0; i < vecLuzFocal.size(); i++) {

			vecLuzFocal[i]->actualizarLuz(personaxePrincipal->posicion, personaxePrincipal->angulo);

			std::string base = "spotLights[" + std::to_string(i) + "].";

			std::string aux = base + "position";
			unsigned int spotLight_position = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_position, 1, glm::value_ptr(vecLuzFocal[i]->posicion));

			aux = base + "direction";
			unsigned int spotLight_direction = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_direction, 1, glm::value_ptr(vecLuzFocal[i]->direccion));

			aux = base + "innerCutOff";
			unsigned int spotLight_innerCutOff = glGetUniformLocation(shader, aux.c_str());
			glUniform1f(spotLight_innerCutOff, vecLuzFocal[i]->innerCutOff);

			aux = base + "outerCutOff";
			unsigned int spotLight_outerCutOff = glGetUniformLocation(shader, aux.c_str());
			glUniform1f(spotLight_outerCutOff, vecLuzFocal[i]->outerCutOff);

			aux = base + "diffuse";
			unsigned int spotLight_diffuse = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_diffuse, 1, glm::value_ptr(vecLuzFocal[i]->difusa));

			aux = base + "specular";
			unsigned int spotLight_specular = glGetUniformLocation(shader, aux.c_str());
			glUniform3fv(spotLight_specular, 1, glm::value_ptr(vecLuzFocal[i]->especular));
		}

	}
	else {
		// Marcamos no shader que non utilizamos luz focal
		unsigned int spot = glGetUniformLocation(shader, "spot");
		glUniform1i(spot, 0);
	}
}

void Mundo::renderizarMiniMapa() {
	float ancho = 400;
	float alto = ancho * PROPORCION_MINIMAPA;
	glViewport(camara->width - ancho - 20, camara->height - alto - 20, ancho, alto);

	// Utilizamos o shader para os obxectos que non tenhen texturas
	glUseProgram(shaderProgramMiniMapa);

	camaraMiniMapa->establecerCamara(personaxePrincipal);
	camaraMiniMapa->actualizarMatrizProxeccionOrtho(25.0f);
	camaraMiniMapa->actualizarMatricesShader(shaderProgram);

	// O obxecto pintamolo doutra cor
	unsigned int loc_cor = glGetUniformLocation(shaderProgramMiniMapa, "cor");
	glUniform1i(loc_cor, 1);

	unsigned int loc_color = glGetUniformLocation(shaderProgramMiniMapa, "color");

	personaxePrincipal->renderizarObxecto();

	for (int i = 0; i < inimigos.size();i++) {
		inimigos[i]->renderizarObxecto();
	}

	glUniform3fv(loc_color, 1, value_ptr(glm::vec3(0, 0.3f, 0)));
	suelo->renderizarSuelo();

}

void Mundo::renderizarEscena() {

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

	personaxePrincipal->renderizarObxecto();
	personaxePrincipal->renderizarBalas();

	for (int i = 0; i < obxectosDecorativos.size(); i++) {
		obxectosDecorativos[i]->renderizarObxecto();
	}

	for (int i = 0; i < inimigos.size();i++) {
		inimigos[i]->renderizarObxecto();
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

	// Actuvamos a variable do shader para iluminar o skyBox
	glUniform1i(loc_skyBox, 1);

	skyBox->renderizarSkyBox();

	renderizarMiniMapa();
}

// Implementación de la función de callback para cambiar el tamaño de la ventana
void Mundo::reescalarVenta(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camara->width = (float)width;
	camara->height = (float)height;
	camara->actualizarMatrizProxeccion();
}

// Funcion que xestiona os controis. Deste xeito cada mundo poderia cambiar, por exemplo, a velocidade de movemento do personaxe
void Mundo::eventoTeclado(int tecla, int accion) {

	// --------------- personaxe principal MOVEMENTOS -------------------------- //
	// 
	// Tecla d: xiro do personaxe a dereita
	if (tecla == 68 && accion != GLFW_RELEASE) {
		personaxePrincipal->angulo -= INCREMENTO_XIRO_PERSONAXE;
	}

	// Tecla a: xiro do personaxe a esquerda
	if (tecla == 65 && accion != GLFW_RELEASE) {
		personaxePrincipal->angulo += INCREMENTO_XIRO_PERSONAXE;
	}

	// Tecla w: desprazarse cara diante
	if (tecla == 87) {

		if (accion == GLFW_PRESS) {
			personaxePrincipal->moverse = true;
		}

		if (accion == GLFW_RELEASE) {
			personaxePrincipal->moverse = false;
		}
	}

	// Tecla s: desprazarse cara atras
	if (tecla == 83) {

		if (accion == GLFW_PRESS) {
			personaxePrincipal->moverse = true;
		}

		if (accion == GLFW_RELEASE) {
			personaxePrincipal->moverse = false;
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
		personaxePrincipal->disparar();
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

