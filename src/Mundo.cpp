#include "encabezados/Mundo.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <random>
#include <iostream>

Mundo::Mundo(PersonaxePrincipal* personaxePrincipal, GLuint shaderProgram,
	float alturaMundo, float* limitesx, float* limitesz,
	std::map<int, int> elementosDecorativos, int nivelMundo)
{

	this->personaxePrincipal = personaxePrincipal;
	this->shaderProgram = shaderProgram;
	this->nivelMundo = nivelMundo;

	xerarSuelo(alturaMundo, limitesx, limitesz);
	xerarElementosDecorativos(elementosDecorativos);
	xerarInimigos(nivelMundo);
}

void Mundo::iniciarMundo() {
	this->camara = new Camara(20.0f, PI / 2.0f, (float)PI / 4.0f, shaderProgram);

	// colocamos ao personaxe principal SOBRE o chan no centro do mesmo
	personaxePrincipal->posicion = glm::vec3(suelo->posicion.x, suelo->posicion.y, suelo->posicion.z);
}

void Mundo::xerarSuelo(float alturaMundo, float* limitesx, float* limitesz) {
	this->suelo = new Suelo(glm::vec3(0, alturaMundo, 0), ESCALA_SUELO, limitesx, limitesz, shaderProgram, FIGURA_CADRADO);
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
		case ID_HERBA:
			rutaOBJ = "recursos/modelos/Herba.obj";
			break;
		}

		int numElementos = iterador->second;

		std::random_device rd;
		std::mt19937 generator(rd());

		// Definir una distribución para generar números reales en un rango
		std::uniform_real_distribution<double> distribucionRadio(2, suelo->limitesz[1]);
		std::uniform_real_distribution<double> distribucionAngulo(0, 2 * PI);

		for (int i = 0; i < numElementos; i++) {

			float radio = (float)distribucionRadio(generator);
			float angulo = (float)distribucionAngulo(generator);

			glm::vec3 posicion(radio * glm::sin(angulo), suelo->posicion.y, radio * glm::cos(angulo));
			glm::vec3 escala(1.0f);

			Obxecto* obxecto = new Obxecto(posicion, escala, shaderProgram, rutaOBJ);
			obxectosDecorativos.push_back(obxecto);
		}
	}
}

void Mundo::xerarInimigos(int nivelInimigos) {
	int numEnemigos = nivelInimigos * 10;

	std::random_device rd;
	std::mt19937 generator(rd());

	// Definir una distribución para generar números reales en un rango
	std::uniform_real_distribution<double> distribucionRadio(5, suelo->limitesz[1]);
	std::uniform_real_distribution<double> distribucionAngulo(0, 2 * PI);

	for (int i = 0; i < numEnemigos; i++) {
		float radio = (float)distribucionRadio(generator);
		float angulo = (float)distribucionAngulo(generator);

		glm::vec3 posicion(radio * glm::sin(angulo), suelo->posicion.y, radio * glm::cos(angulo));
		glm::vec3 escala(1.0f);

		Enemigo* enemigo = new Enemigo(posicion, escala, shaderProgram, FIGURA_CUBO, 1, personaxePrincipal);

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

void Mundo::renderizarEscena() {
	// Cor da luz que ilumina os obxectos
	glm::vec3 corLuz(1.0f, 1.0f, 1.0f);

	glm::vec3 dirLight_direccion;
	glm::vec3 dirLight_ambiente;
	glm::vec3 dirLight_difusa;
	glm::vec3 dirLight_espec;

	glm::vec3 spotLight_posicion;
	glm::vec3 spotLight_direccion;
	glm::vec3 spotLight_difusa;
	glm::vec3 spotLight_espec;

	float spotLight_corte;

	if (nivelMundo == 4) {
		dirLight_direccion = glm::vec3(0, -3, 5);
		dirLight_ambiente = glm::vec3(0.0f);
		dirLight_difusa = glm::vec3(0.3f);
		dirLight_espec = glm::vec3(0.0f);

		spotLight_posicion = personaxePrincipal->posicion + glm::vec3(0, 2.0f, 0);

		// Provisional, isto debeo facer o personaxe principal e devolver a direccion
		glm::mat4 rotacion = rotate(glm::mat4(), personaxePrincipal->angulo, glm::vec3(0, 1, 0));
		spotLight_direccion =  rotacion * glm::vec4(0, 0, 1.0f, 0);

		spotLight_difusa = glm::vec3(0.0f, 0.8f, 0.8f);
		spotLight_espec = glm::vec3(0.0f);
		spotLight_corte = 0.85f;
	}
	else {
		dirLight_direccion = glm::vec3(0, -5, 3);
		dirLight_ambiente = glm::vec3(0.3f);
		dirLight_difusa = glm::vec3(0.8f);
		dirLight_espec = glm::vec3(0);

		spotLight_posicion = glm::vec3(0);
		spotLight_direccion = glm::vec3(0);
		spotLight_difusa = glm::vec3(0);
		spotLight_espec = glm::vec3(0);
		spotLight_corte = 2;
	}

	// Establecemos a posicion da camara 
	unsigned int viewPos = glGetUniformLocation(shaderProgram, "viewPos");
	glUniform3fv(viewPos, 1, glm::value_ptr(camara->posicionCamara));
	// Establecemos a luz direccional
	unsigned int dirLight_direction = glGetUniformLocation(shaderProgram, "dirLight.direction");
	glUniform3fv(dirLight_direction, 1, glm::value_ptr(dirLight_direccion));
	unsigned int dirLight_ambient = glGetUniformLocation(shaderProgram, "dirLight.ambient");
	glUniform3fv(dirLight_ambient, 1, glm::value_ptr(dirLight_ambiente));
	unsigned int dirLight_diffuse = glGetUniformLocation(shaderProgram, "dirLight.diffuse");
	glUniform3fv(dirLight_diffuse, 1, glm::value_ptr(dirLight_difusa));
	unsigned int dirLight_especular = glGetUniformLocation(shaderProgram, "dirLight.especular");
	glUniform3fv(dirLight_especular, 1, glm::value_ptr(dirLight_espec));


	unsigned int spotLight_position = glGetUniformLocation(shaderProgram, "spotLight.position");
	glUniform3fv(spotLight_position, 1, glm::value_ptr(spotLight_posicion));
	unsigned int spotLight_direction = glGetUniformLocation(shaderProgram, "spotLight.direction");
	glUniform3fv(spotLight_direction, 1, glm::value_ptr(spotLight_direccion));
	unsigned int spotLight_cutOff = glGetUniformLocation(shaderProgram, "spotLight.cutOff");
	glUniform1f(spotLight_cutOff, spotLight_corte);
	unsigned int spotLight_diffuse = glGetUniformLocation(shaderProgram, "spotLight.diffuse");
	glUniform3fv(spotLight_diffuse, 1, glm::value_ptr(spotLight_difusa));
	unsigned int spotLight_specular = glGetUniformLocation(shaderProgram, "spotLight.specular");
	glUniform3fv(spotLight_specular, 1, glm::value_ptr(spotLight_espec));

	establecerCamara();

	// Renderizamos os obxectos
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Provisional mentres non texturas
	glm::vec3 ambiente;
	glm::vec3 difusa;
	glm::vec3 especular;
	float brillo = 10.0f;

	if (nivelMundo == 1) {
		ambiente = glm::vec3(0.0f, 0.2f, 0.0f);
		difusa = glm::vec3(0.0f, 0.2f, 0.0f);
		especular = glm::vec3(1.0f);
		brillo = 10.0f;
	}
	else if (nivelMundo == 2) {
		ambiente = glm::vec3(0.4f, 0.1f, 0.2f);
		difusa = glm::vec3(0.4f, 0.3f, 0.2f);
		especular = glm::vec3(1.0f);
		brillo = 15.0f;
	}
	else if (nivelMundo == 3) {
		ambiente = glm::vec3(0.0f, 0.1f, 0.0f);
		difusa = glm::vec3(0.0f, 0.1f, 0.0f);
		especular = glm::vec3(1.0f);
		brillo = 4.0f;
	}
	else if (nivelMundo == 4) {
		ambiente = glm::vec3(0.0f, 0.1f, 0.0f);
		difusa = glm::vec3(0.0f, 0.2f, 0.0f);
		especular = glm::vec3(1.0f);
		brillo = 1.0f;
	}

	// Damoslle a cor do material ao obxecto
	unsigned int ambient = glGetUniformLocation(shaderProgram, "material.ambient");
	glUniform3fv(ambient, 1, glm::value_ptr(ambiente));
	unsigned int diffuse = glGetUniformLocation(shaderProgram, "material.diffuse");
	glUniform3fv(diffuse, 1, glm::value_ptr(difusa));
	unsigned int specular = glGetUniformLocation(shaderProgram, "material.specular");
	glUniform3fv(specular, 1, glm::value_ptr(especular));
	unsigned int shininess = glGetUniformLocation(shaderProgram, "material.shininess");
	glUniform1f(shininess, brillo);


	suelo->renderizarSuelo();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	personaxePrincipal->renderizarObxecto();

	for (int i = 0; i < obxectosDecorativos.size(); i++) {
		obxectosDecorativos[i]->renderizarObxecto();
	}

	for (int i = 0; i < inimigos.size();i++) {
		inimigos[i]->renderizarObxecto();
	}

}

// Implementación de la función de callback para cambiar el tamaño de la ventana
void Mundo::reescalarVenta(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camara->width = width;
	camara->height = height;
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
		camara->beta = fmin(camara->beta + INCREMENTO_XIRO_CAMARA_XERAL, PI / 2.0f - UNIDADE_GRAO_EN_RADIANS);
		break;
	case XIRO_CAMARA_ABAIXO:
		camara->beta = fmax(camara->beta - INCREMENTO_XIRO_CAMARA_XERAL, -PI / 2.0f + UNIDADE_GRAO_EN_RADIANS);
		break;
	case ACERCAR_CAMARA:
		camara->radio = fmax(camara->radio - INCREMENTO_RADIO_CAMARA_XERAL, MIN_DIST_CAMARA_XERAL);
		break;
	case AFASTAR_CAMARA:
		camara->radio = fmin(camara->radio + INCREMENTO_RADIO_CAMARA_XERAL, MAX_DIST_CAMARA_XERAL);
		break;
	}
}

