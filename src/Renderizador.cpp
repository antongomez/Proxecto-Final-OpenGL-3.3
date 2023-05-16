#include "encabezados/Renderizador.hpp"
#include "encabezados/definicions.h"

#include <glm/gtc/type_ptr.hpp>

Renderizador::Renderizador() {
	this->shaderProgram = shaderProgram;
	this->camara = new Camara(20.0f, PI / 2.0f, (float)PI / 4.0f);
}

void Renderizador::setShaderProgram(GLuint shaderProgram) {
	this->camara->shaderProgram = shaderProgram;
	this->shaderProgram = shaderProgram;
}

void Renderizador::establecerCamara(int tipoCamara, glm::vec3 target) {
	switch (tipoCamara) {
	case CAMARA_XERAL:
		// Colocamos a camara
		camara->vistaXeral(target);
		break;
	case CAMARA_TERCEIRA_PERSOA:
		break;
	}

	// Actualizamos a matriz de proxeccion
	camara->actualizarMatrizProxeccion();
}

void Renderizador::renderizarEscena() {
	// Cor da luz que ilumina os obxectos
	glm::vec3 corLuz(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < escena.size();i++) {

		// Establecemos a cor da luz
		unsigned int cor_luz = glGetUniformLocation(shaderProgram, "cor_luz");
		glUniform3fv(cor_luz, 1, glm::value_ptr(corLuz));

		// Desactivamos o flag para calcular a cor dos obxectos cargados
		unsigned int obxecto_cargado = glGetUniformLocation(shaderProgram, "obxecto_cargado");
		glUniform1i(obxecto_cargado, 0);

		escena[i]->renderizarObxecto();
	}
}

void Renderizador::introducirElementoEscena(Obxecto* obxecto) {
	escena.push_back(obxecto);
}

// Implementación de la función de callback para cambiar el tamaño de la ventana
void Renderizador::reescalarVenta(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	camara->width = width;
	camara->height = height;
	camara->actualizarMatrizProxeccion();
}

void Renderizador::moverCamara(int tipoMovemento) {
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
		camara->beta = fmin(camara->beta + INCREMENTO_XIRO_CAMARA_XERAL, PI / 2.0f - UNIDADE_GRAO_EN_RADIANS);
		break;
	case XIRO_CAMARA_ABAIXO:
		// Limite superior de 90 grados
		camara->beta = fmax(camara->beta - INCREMENTO_XIRO_CAMARA_XERAL, 0.0f + UNIDADE_GRAO_EN_RADIANS);
		break;
	case ACERCAR_CAMARA:
		camara->radio = fmax(camara->radio - INCREMENTO_RADIO_CAMARA_XERAL, MIN_DIST_CAMARA_XERAL);
		break;
	case AFASTAR_CAMARA:
		camara->radio = fmin(camara->radio + INCREMENTO_RADIO_CAMARA_XERAL, MAX_DIST_CAMARA_XERAL);
		break;
	}
}

